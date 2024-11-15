main: list.o main.o
	clang -o main list.o main.o
list.o: list.h list.c
	clang -c list.c
main.o: list.h main.c
	clang -c main.c
clean:
	rm -f *.o main
