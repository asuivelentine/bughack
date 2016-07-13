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
content/appendix.tex: content/appendix.md
	pandoc -o $@ $<



pdf: content/abbreviations.tex content/abstract.tex content/affirmation.tex content/ausblick.tex content/eigeneKapitel.tex content/einleitung.tex content/fazit.tex content/grundlagen.tex content/appendix.tex
	cd ../protokolle/ && $(MAKE) all
	cd ../aufgaben/bank && $(MAKE) pandoc
	cd ../aufgaben/server_login && $(MAKE) pandoc
	cd ../aufgaben/private_calendar  && $(MAKE) pandoc
	cd ../aufgaben/rop && $(MAKE) pandoc
	cd ../aufgaben/kontaktverwaltung && $(MAKE) pandoc
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
	cd ../protokolle/ && $(MAKE) clean
	cd ../aufgaben/bank && $(MAKE) clean
	cd ../aufgaben/server_login && $(MAKE) clean
	cd ../aufgaben/private_calendar  && $(MAKE) clean
	cd ../aufgaben/rop && $(MAKE) clean
	cd ../aufgaben/kontaktverwaltung && $(MAKE) clean
