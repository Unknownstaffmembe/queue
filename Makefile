uqueue.o: uqueue.c uqueue.h
	gcc -g -c uqueue.c -l pthread -o uqueue.o

.PHONY: release test global remove

release: uqueue.c uqueue.h
	gcc -O2 -c uqueue.c -l pthread -o uqueue.o

test: uqueue.o test.c
	gcc -g test.c uqueue.o -o test.o

global:
	gcc -O2 -c uqueue.c -l pthread -o uqueue.o
	cp uqueue.h /usr/local/include/uqueue.h
	cp uqueue.o /usr/local/lib/libuqueue.a

remove:
	rm /usr/local/include/uqueue.h
	rm /usr/local/lib/libuqueue.o
