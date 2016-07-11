all: pandoc
SOURCES=$(wildcard ./*.md)

dokuvorgehen.tex: dokuvorgehen.md
	pandoc -o $@ $<
stellung.tex: stellung.md
	pandoc -o $@ $<


pandoc:dokuvorgehen.tex stellung.tex

clean:
	rm -f *.tex
