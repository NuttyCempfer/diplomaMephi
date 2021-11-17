all: main.c mainmenu.c mainmenu.h DetMatrix2.c determ.h MultiMatrix.c multy.h parser.c parser.h matr.c matr.h main

clean:
	rm -rf main.o mainmenu.o DetMatrix2.o MultiMatrix.o parser.o matr.o main

main: main.o mainmenu.o DetMatrix2.o MultiMatrix.o parser.o matr.o
	cc -o main mainmenu.o DetMatrix2.o MultiMatrix.o parser.o matr.o main.o


.c.o:
	cc -c -o $@ $<
