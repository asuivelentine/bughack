all: pdf
SOURCES=$(wildcard content/*.md)

content/abbreviations.tex: content/abbreviations.md
	pandoc -o $@ $<
content/abstract.tex: content/abstract.md
	pandoc -o $@ $<
content/affirmation.tex: content/affirmation.md
	pandoc -o $@ $<
content/ausblick.tex: content/ausblick.md
	pandoc -o $@ $<
content/eigeneKapitel.tex: content/eigeneKapitel.md
	pandoc -o $@ $<
content/einleitung.tex: content/einleitung.md
	pandoc -o $@ $<
content/fazit.tex: content/fazit.md
	pandoc -o $@ $<
content/grundlagen.tex: content/grundlagen.md
	pandoc -o $@ $<



pdf: content/abbreviations.tex content/abstract.tex content/affirmation.tex content/ausblick.tex content/eigeneKapitel.tex content/einleitung.tex content/fazit.tex content/grundlagen.tex
	pdflatex main

clean:
	rm -f *.aux
	rm -f *.log
	rm -f *.lot
	rm -f *.lof
	rm -f *.out
	rm -f *.bbl
	rm -f *.blg
	rm -f *.toc
	rm -f *.idx
	rm -f *.pdf
	rm -f content/*.aux
