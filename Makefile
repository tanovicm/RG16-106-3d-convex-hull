PROGRAM = chull
CC      = gcc
LDLIBS  = -lglut -lGLU -lGL -lm
FLAGZ   = -Wall -Wextra

$(PROGRAM): main.o list.o point.o chull.o vector.o plain.o
	$(CC) $(FLAGZ) -o  $(PROGRAM) $^ $(LDLIBS) 

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)