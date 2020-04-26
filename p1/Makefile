CFLAGS = -I.
CC = gcc
OBJECTS = main.o func1.o func2.o

all: programa punteros

programa: $(OBJECTS)
	$(CC) $(OBJECTS) -o main
	rm -rf $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

func1.o: func1.c
	$(CC) $(CFLAGS) -c func1.c

func2.o: func2.c
	$(CC) $(CFLAGS) -c func2.c

punteros: punteros_2.c
	$(CC) punteros_2.c -o punteros

clean:
	rm -rf main punteros $(OBJECTS)
