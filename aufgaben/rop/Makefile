all: pandoc
SOURCES=$(wildcard ./*.md)

readme.tex: readme.md
	pandoc -o $@ $<


pandoc: readme.tex

clean:
	rm -f *.tex
