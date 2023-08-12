CFLAGS = --std=c99 -pedantic-errors

ALL: main

debug: CFLAGS += -g
debug: main

main: main.o escalonador.o logtree.o fila_fifo.o
	$(CC) $(CFLAGS) main.o escalonador.o logtree.o fila_fifo.o -o main

main.o: main.c escalonador.h
	$(CC) $(CFLAGS) -c main.c

escalonador.o: escalonador.c escalonador.h
	$(CC) $(CFLAGS) -c escalonador.c

logtree.o: logtree.c logtree.h
	$(CC) $(CFLAGS) -c logtree.c

fila_fifo.o: fila_fifo.c fila_fifo.h
	$(CC) $(CFLAGS) -c fila_fifo.c

clean:
	rm -f *.o main
