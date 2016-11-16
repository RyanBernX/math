include ../Make.global_options

PDF=161110-1.pdf

default: all

all: $(PDF)

%.pdf: %.tex
	$(LATEX) $(LATEXFLAG) $< > /dev/null 2>&1


