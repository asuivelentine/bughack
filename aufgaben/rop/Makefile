all: pandoc
SOURCES=$(wildcard ./*.md)

readme.tex: readme.md
	pandoc -o $@ $<

dokumentation.tex: dokumentation.md
	pandoc -o $@ $<

pandoc: readme.tex dokumentation.tex

clean:
	rm -f *.tex
