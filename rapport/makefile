include ../makefile.inc

FIGURES = figures

all: rapport.pdf

rapport.pdf: rapport.tex
	cd $(FIGURES) && make
	pdflatex $<

clean:
	rm -f *.aux *.log *.gz *.pdf *~

cleanall: clean
	cd $(FIGURES) && make clean

force_look:
	true

.PHONY: all clean cleanall

