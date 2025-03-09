all: cliente.o fila.o
	gcc cliente.o fila.o -o cliente.bin

cliente.o: cliente.c fila.h
	gcc -std=c99 -Wall -Werror -c cliente.c

fila.o: fila.c fila.h
	gcc -std=c99 -Wall -Werror -c fila.c

clean:
	rm -f *.o
	rm -f cliente.bin
