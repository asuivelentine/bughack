SOURCES=$(wildcard ./*.md)

pandoc: aufgabenstellung.tex dokuvorgehen.tex

aufgabenstellung.tex: aufgabenstellung.md
	pandoc -o $@ $<
dokuvorgehen.tex: dokuvorgehen.md
	pandoc -o $@ $<

clean:
	rm -f *.tex

