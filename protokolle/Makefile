all: protokolle
SOURCES=$(wildcard ../protokolle/*.tex)

protokoll_2016_03_17.tex: protokoll_2016_03_17.md
	pandoc -o $@ $<
protokoll_2016_03_24.tex: protokoll_2016_03_24.md
	pandoc -o $@ $<
protokoll_2016_04_07.tex: protokoll_2016_04_07.md
	pandoc -o $@ $<
protokoll_2016_05_31.tex: protokoll_2016_05_31.md
	pandoc -o $@ $<
protokoll_2016_06_28.tex: protokoll_2016_06_28.md
	pandoc -o $@ $<



protokolle: protokoll_2016_03_17.tex protokoll_2016_03_24.tex protokoll_2016_04_07.tex protokoll_2016_05_31.tex protokoll_2016_06_28.tex

clean:
	rm -f *.tex
