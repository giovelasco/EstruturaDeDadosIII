CFILE  = funcionalidades.c exemplo.c 
HFILE = funcionalidades.h header.h register.h 

all :
	gcc -g -o exec $(CFILE) $(HFILE)

run : exec
	./exec

clean :
	rm *.o exec