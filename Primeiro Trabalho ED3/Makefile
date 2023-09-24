CFILE  = funcionalidades.c arquivos.c registros.c main.c
HFILE = funcionalidades.h arquivos.h registros.h

all :
	gcc -g -o exec $(CFILE) $(HFILE)

run : exec
	./exec

clean :
	rm *.o exec