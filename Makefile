queue.o: queue.c queue.h
	gcc -g -c queue.c -l pthread -o queue.o

.PHONY: release test global remove

release: queue.c queue.h
	gcc -O2 -c queue.c -l pthread -o queue.o

test: queue.o test.c
	gcc -g test.c queue.o -o test.o

global:
	gcc -O2 -c queue.c -l pthread -o queue.o
	cp queue.h /usr/local/include/queue.h
	cp queue.o /usr/local/lib/queue.o

remove:
	rm /usr/local/include/queue.h
	rm /usr/local/lib/queue.o
