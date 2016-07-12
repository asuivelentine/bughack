SOURCES=$(wildcard ./*.md)
CC = clang
CFLAGS = -std=gnu11 -march=native -Wall -Wextra -pedantic-errors -Oz -s
LIBS = -lcurses -lcrypt
SRC = main.c
OUT = main

all: prog

prog:
	@echo "  [PROG]"
	@$(CC) $(CFLAGS) $(LIBS) -o $(OUT) $(SRC)

pandoc: aufgabenstellung.tex

aufgabenstellung.tex: aufgabenstellung.md
	pandoc -o $@ $<

clean:
	rm -f main
	rm -f aufgabenstellung.tex
