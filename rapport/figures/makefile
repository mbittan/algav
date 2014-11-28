include ../../makefile.inc

FIGURES: briandais_test.pdf graph_template.pdf

all: $(FIGURES)

%.pdf: %.tex
	pdflatex $<

clean:
	rm -f *.aux *.log *.gz *.pdf *~

.PHONY: all clean

