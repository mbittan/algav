include ../makefile.inc

TEXFLAGS = -shell-escape

FIGURES = figures

all: rapport.pdf slides.pdf th.pdf

th.pdf : triehybride.tex
	cd $(FIGURES) && make
	pdflatex $<

rapport.pdf: rapport.tex
	cd $(FIGURES) && make
	pdflatex $(TEXFLAGS) $<

slides.pdf: slides.tex
	cd $(FIGURES) && make
	pdflatex $<

clean:
	rm -f *.aux *.log *.gz *.pdf *~ *.nav *.snm *.toc *.vrb *.out *.pyg

cleanall: clean
	cd $(FIGURES) && make clean

force_look:
	true

.PHONY: all clean cleanall

