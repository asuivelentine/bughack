SOURCES=$(wildcard ./*.md)
all: pandoc

pandoc: ./easy_heapoverflow/aufgabenstellung.tex ./easy_integer_underflow/aufgabenstellung.tex ./easy_stackoverflow/dokumentation.tex ./hard_grub2-CVE-2015-8370-rebuild/aufgabenstellung.tex ./medium_rop_attack/aufgabenstellung.tex ./other_stuff/aslr_test/README.tex ./other_stuff/brute_example/README.tex

./easy_heapoverflow/aufgabenstellung.tex: ./easy_heapoverflow/aufgabenstellung.md
	pandoc -o $@ $<

./easy_integer_underflow/aufgabenstellung.tex: ./easy_integer_underflow/aufgabenstellung.md
	pandoc -o $@ $<

./easy_stackoverflow/dokumentation.tex: ./easy_stackoverflow/dokumentation.md
	pandoc -o $@ $<

./hard_grub2-CVE-2015-8370-rebuild/aufgabenstellung.tex: ./hard_grub2-CVE-2015-8370-rebuild/aufgabenstellung.md
	pandoc -o $@ $<

./medium_rop_attack/aufgabenstellung.tex: ./medium_rop_attack/aufgabenstellung.md
	pandoc -o $@ $<

./other_stuff/aslr_test/README.tex: ./other_stuff/aslr_test/README.md
	pandoc -o $@ $<

./other_stuff/brute_example/README.tex: ./other_stuff/brute_example/README.md
	pandoc -o $@ $<

clean:
	find . -type f -name '*.tex' -delete
