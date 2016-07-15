SOURCES=$(wildcard ./*.md)
all: prog

prog: main.o handler.o lib.o
	gcc -ggdb -fno-inline-small-functions -o prog main.o handler.o lib.o server.c -pthread -lcrypt

main.o: main.c main.h types.h
	gcc -ggdb -fno-inline-small-functions -c main.c main.h types.h

handler.o: handler.c handler.h types.h
	gcc -ggdb -fno-inline-small-functions -c handler.c handler.h types.h

lib.o: lib.c types.h
	gcc -ggdb -fno-inline-small-functions -c lib.c types.h

Aufgabenstellung.tex: Aufgabenstellung.md
	pandoc -o $@ $<
dokuvorgehen.tex: dokuvorgehen.md
	pandoc -o $@ $<

pandoc: Aufgabenstellung.tex dokuvorgehen.tex

Aufgabenstellung.tex: Aufgabenstellung.md
	pandoc -o $@ $<

clean:
	rm -f *.tex
	rm -f prog
	rm -f *.o
	rm -f *.h.gch
