
a.out : mylib.a
	gcc main.c -L. mylib.a -lncurses

mylib.a : fun.o admin.o user.o
	ar rcs mylib.a fun.o admin.o user.o

fun.o : fun.c fun.h
	gcc -c fun.c

admin.o : admin.c fun.h
	gcc -c admin.c

user.o : user.c fun.h
	gcc -c user.c

clean :
	rm *.o
