all :
	gcc -o programaTrab *.c

run : 
	./programaTrab

val :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./programaTrab < teste.in > teste.out