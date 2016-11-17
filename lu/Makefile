CC=gcc
CFLAG=
CDEBUG=-g -Wall
LIB=-lm

DOXYGEN=doxygen
DOXY_CONFIG=Doxyfile

RM=rm
RM_FLAG=-f

OBJ=lu_impls.o main.o

.PHONY: exec clean docs

%.o: %.c
	$(CC) $(CDEBUG) -c $< $(CFLAG)

exec: $(OBJ)
	$(CC) $(CDEBUG) -o main.x $^ $(LIB) $(CFLAG)

clean:
	$(RM) $(RM_FLAG) main.x *.o

docs:
	$(DOXYGEN) $(DOXY_CONFIG)

