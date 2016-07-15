all: pandoc
SOURCES=$(wildcard ./*.md)

Aufgabenstellung.tex: Aufgabenstellung.md
	pandoc -o $@ $<
dokuvorgehen.tex: dokuvorgehen.md
	pandoc -o $@ $<


pandoc: Aufgabenstellung.tex dokuvorgehen.tex

clean:
	rm -f *.tex
