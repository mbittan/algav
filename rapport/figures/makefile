include ../../makefile.inc

FIGURES: briandais_test.pdf graph_template.pdf trie_hybride.pdf

all: $(FIGURES)

%.pdf: %.tex
	pdflatex $<

clean:
	rm -f *.aux *.log *.gz *.pdf *~ *.png

.PHONY: all clean

