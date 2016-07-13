TARGET   = kontaktverwaltung
CC       = gcc -std=c99 -c
CFLAGS   = -Wall -I.
LINKER   = gcc -o
LFLAGS   = -Wall
SOURCES  := $(wildcard *.c)
INCLUDES := $(wildcard *.h)
PANDOC_SOURCES =$(wildcard ./*.md)
OBJECTS  := $(SOURCES:.c=*.o)
rm       = rm -f

$(TARGET): obj
	@$(LINKER) $(TARGET) $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

obj: $(SOURCES) $(INCLUDES)
	@$(CC) $(CFLAGS) $(SOURCES)
	@echo "Compilation complete!"

pandoc: readme.tex

readme.tex: readme.md
	pandoc -o $@ $<

clean:
	@$(rm) $(TARGET) $(OBJECTS)
	rm -rf *.tex
	@echo "Cleanup complete!"

