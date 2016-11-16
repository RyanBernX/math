include ../Make.global_options

PDF=problems.pdf problems_and_solution.pdf

.PHONY: clean

default: all

all: $(PDF)

%.pdf: %.tex
	$(LATEX) $(LATEXFLAG) $< > /dev/null 2>&1

clean:
	$(RM) $(RM_FLAG) $(PDF)

