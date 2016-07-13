all: pandoc
SOURCES=$(wildcard ./*.md)

Aufgabenstellung.tex: Aufgabenstellung.md
	pandoc -o $@ $<


pandoc: Aufgabenstellung.tex

clean:
	rm -f *.tex
