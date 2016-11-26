.PHONY : docs clean
DOCS=index
UTILS=../utils/
PREFIX=../

HDOCS=$(addsuffix .html, $(DOCS))
PHDOCS=$(addprefix $(PREFIX), $(HDOCS))

docs : $(PHDOCS)

$(PREFIX)%.html : %.jemdoc MENU
	$(UTILS)jemdoc.py -o $@ $<
	cp  eqs/*.png ../eqs

clean :
	rm -f $(PREFIX)*.html
