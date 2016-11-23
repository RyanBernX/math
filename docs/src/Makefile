.PHONY : docs clean
DOCS=index
UTILS=../utils/
PREFIX=../

HDOCS=$(addsuffix .html, $(DOCS))
PHDOCS=$(addprefix $(PREFIX), $(HDOCS))

docs : $(PHDOCS)

$(PREFIX)%.html : %.jemdoc MENU
	$(UTILS)jemdoc.py -o $@ $<
	rm -f ../eqs
	cp -r eqs ../

clean :
	rm -f $(PREFIX)*.html
