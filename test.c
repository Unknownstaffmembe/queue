#include <stdio.h>
#include "uqueue.h"
#define ITERATIONS 100

int main()
{
	struct uqueue q;
	int i, it, c;

	queue_init(&q, 10, 1, sizeof(int));
	for (i = 0; i < ITERATIONS; i++) {
		it = (i * 2);
		queue_add(&q, &it);
	};
	for (i = 0; i < ITERATIONS; i++) {
		it = queue_get(&q, &c);
		printf("%d\n", c);
	};
	i = queue_get(&q, &c); // shouldn't write to &c and, should return -1
	printf("%d %d\n", c, i);

	return 0;
}
