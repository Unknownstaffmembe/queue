queue.o: queue.c queue.h
	gcc -g -c queue.c -l pthread -o queue.o

.PHONY: release test

release: queue.c queue.h
	gcc -O2 -c queue.c -l pthread -o queue.o

test: queue.o test.c
	gcc -g test.c queue.o -o test.o
