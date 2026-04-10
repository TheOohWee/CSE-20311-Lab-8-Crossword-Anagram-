

runcrossword: cwfunc.o crossword.o
	gcc cwfunc.o crossword.o -o runcrossword

cwfunc.o: cwfunc.c cwfunc.h
	gcc -c cwfunc.c -o cwfunc.o

crossword.o: crossword.c cwfunc.h
	gcc -c crossword.c -o crossword.o

clean: 
		rm *.o
		rm runcrossword
