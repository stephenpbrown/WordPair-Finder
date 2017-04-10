CC=gcc
COPTS = -g -c -std=c99 -Wall -pedantic
LOPTS = -g
INCDIRS = -I$(GET_WORD)/encs_share/cs/class/cs360/include
LIBDIRS = -L$(GET_WORD)/encs_share/cs/class/cs360/lib

wordpairs: main.o ht.o
	$(CC) $(LOPTS) $(LIBDIRS) -o wordpairs main.o ht.o -lget

main.o:	main.c ht.h
	$(CC) $(COPTS) $(INCDIRS) main.c 

ht.o: ht.c ht.h
	$(CC) $(COPTS) ht.c

clean:
	rm wordpairs main.o ht.o
