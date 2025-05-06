CC=gcc

output: main.o functii.o
	$(CC) -Wall -pthread functii.o main.o -o output

main.o: main.c functii.h
	$(CC) -c -Wall main.c

functii.o: functii.c functii.h
	$(CC) -c -Wall functii.c

.PHONY: clean

clean: 
	rm -f *.o output
