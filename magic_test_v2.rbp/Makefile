include ../Make.global_options

PDF=problems.pdf 

.PHONY: clean

default: all

all: $(PDF)

%.pdf: %.tex
	$(LATEX) $(LATEXFLAG) $< > /dev/null 2>&1

clean:
	$(RM) $(RM_FLAG) $(LATEX_CLEAN) $(PDF)

