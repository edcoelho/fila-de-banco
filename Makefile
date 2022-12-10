ALL: main

main: main.o escalonador.o logtree.o fila_fifo.o
	gcc --std=c99 -pedantic-errors main.o escalonador.o logtree.o fila_fifo.o -o main

main.o: main.c escalonador.h
	gcc --std=c99 -pedantic-errors -c main.c

escalonador.o: escalonador.c escalonador.h
	gcc --std=c99 -pedantic-errors -c escalonador.c

logtree.o: logtree.c logtree.h
	gcc --std=c99 -pedantic-errors -c logtree.c

fila_fifo.o: fila_fifo.c fila_fifo.h
	gcc --std=c99 -pedantic-errors -c fila_fifo.c

clean:
	rm -f *.o main
