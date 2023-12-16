all :
	gcc -o programaTrab *.c

run : 
	./programaTrab

val :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./programaTrab < teste.in > bingrafo6.out

comp :
	@echo "Comparando arquivos de saída..."
	@diff -u teste.out 3.out && echo "Os arquivos são iguais." || echo "Os arquivos são diferentes."
