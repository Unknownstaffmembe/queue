#ifndef LLIST_INCLUDED
#define LLIST_INCLUDED
// badly designed queue
#include <pthread.h>

struct uqueue;

extern int uqueue_init(struct uqueue *q, unsigned long int in, unsigned long int inc, size_t ts); // uqueue, num of indexes, increment size, type size
extern int uqueue_add(struct uqueue *q, void *v); // uqueue, val ptr
extern int uqueue_get(struct uqueue *q, void *vc); // uqueue, val container

struct uqueue {
	void *arr; // ptr array
	pthread_mutex_t im, rm; // insert mutex, read mutex
	unsigned long int h, t, in, inc; // head index, tail index, num of indexes, increment size (indexes)
	size_t ts; // type size
};

#endif
