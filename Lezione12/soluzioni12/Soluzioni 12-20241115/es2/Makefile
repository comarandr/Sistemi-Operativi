main: list.o tree.o main.o
	clang -o main list.o tree.o main.o
list.o: list.h list.c
	clang -c list.c
tree.o: list.h tree.h tree.c
	clang -c tree.c
main.o: tree.h main.c
	clang -c main.c
clean:
	rm -f *.o main
