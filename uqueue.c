#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "uqueue.h"

// local functions
inline static int raa(struct uqueue *q) // realloc array, array, new size
{
	void *narr; // new array
	unsigned long int ns; // new size

	ns = (q->inc + q->in) * q->ts;
	narr = realloc(q->arr, ns);

	if (narr == NULL) return -1;

	q->arr = narr;
	q->in += q->inc;

	return 0;
}

inline static void shft(struct uqueue *q) // shift array
{
	unsigned long int nt; // new tail
	size_t s; // bytes to copy/move

	pthread_mutex_lock(&(q->rm));
	nt = (q->t - q->h);
	s = nt * q->ts;
	memcpy(q->arr, q->arr + q->h * q->ts, s);
	q->h = 0;
	q->t = nt;
	pthread_mutex_unlock(&(q->rm));
	return;
}

// global functions
int uqueue_init(struct uqueue *q, unsigned long int in, unsigned long int inc, size_t ts)
{
	void *arr;

	arr = malloc(in * ts);
	if (arr == NULL) return -1;

	q->arr = arr;
	pthread_mutex_init(&(q->im), NULL);
	pthread_mutex_init(&(q->rm), NULL);
	q->inc = inc;
	q->in = in;
	q->h = 0;
	q->t = 0;
	q->ts = ts;

	return 0;
}

int uqueue_add(struct uqueue *q, void *v)
{
	pthread_mutex_lock(&(q->im));
	if (q->t == q->in) {
		if (q->h == 0) {
			if (raa(q) == -1) {
				pthread_mutex_unlock(&(q->im));
				pthread_mutex_unlock(&(q->rm));
				return -1;
			}
		} else {
			shft(q);
		};
	};
	memcpy(q->arr + q->t * q->ts, v, q->ts);
	q->t++;
	pthread_mutex_unlock(&(q->im));
	return 0;
}

int uqueue_get(struct uqueue *q, void *vc)
{
	pthread_mutex_lock(&(q->rm));
	if (q->t == q->h) {
		pthread_mutex_unlock(&(q->rm));
		return -1;
	};
	memcpy(vc, q->arr + q->h * q->ts, q->ts);
	q->h++;
	pthread_mutex_unlock(&(q->rm));
	return 0;
}
