#ifndef LLIST_INCLUDED
#define LLIST_INCLUDED
// thread safe queue
#include <pthread.h>

struct queue_t;

extern int queue_init(struct queue_t *q, unsigned long int inc, unsigned long int in, size_t ts); // queue, increment size, num of indexes, type size
extern int queue_add(struct queue_t *q, void *v); // queue, val ptr
extern int queue_get(struct queue_t *q, void *vc); // queue, val container

struct queue_t {
	void *arr; // ptr array
	pthread_mutex_t im, rm; // insert mutex, read mutex
	unsigned long int h, t, in, inc; // head index, tail index, num of indexes, increment size (indexes)
	size_t ts; // type size
};

#endif
