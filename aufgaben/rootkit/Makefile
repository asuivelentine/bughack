SOURCES=$(wildcard ./*.md)

pandoc: aufgabenstellung.tex

aufgabenstellung.tex: aufgabenstellung.md
	pandoc -o $@ $<

clean:
	rm -f *.tex

