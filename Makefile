include ./Make.global_options

default: all

all:
	@( \
	for f in `ls | grep .*\.rbp`; \
	do \
		$(CD) $$f && $(MAKE); \
		$(ECHO) Making pdf in $$f; \
		$(CD) ..; \
	done );

