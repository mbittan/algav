include ../../makefile.inc

FIGURES: briandais_test.pdf graph_template.pdf trie_hybride.pdf mem.png trees.png insert.png

all: $(FIGURES)

%.pdf: %.tex
	pdflatex $<

mem.png: plot_mem mem.dat
	gnuplot $<

trees.png: plot_trees trees.dat
	gnuplot $<

insert.png: plot_insert insert.dat
	gnuplot $<

clean:
	rm -f *.aux *.log *.gz *.pdf *~ *.png

.PHONY: all clean

