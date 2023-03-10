CC := gcc
KEYS := -g -Wall -Werror -Wredundant-decls -std=c99  -Wpedantic -Wextra -Wvla
ODIR := ./out
SRCDIR := ./src
INCDIR := ./inc
CONST_HEAD := $(INCDIR)/errors.h $(INCDIR)/structures.h $(INCDIR)/colors.h
OBJS := $(ODIR)/io.o $(ODIR)/graphvis.o $(ODIR)/timer.o $(ODIR)/mem_alloc.o $(ODIR)/operations.o
LIBS := -Iinc 

all : app.exe

app.exe : $(OBJS) $(ODIR)/main.o
	$(CC) $^ -o $@

$(ODIR)/io.o : $(SRCDIR)/io.c $(INCDIR)/io.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/io.c -o $@ $(LIBS)

$(ODIR)/timer.o : $(SRCDIR)/timer.c $(INCDIR)/timer.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/timer.c -o $@ $(LIBS)

$(ODIR)/graphvis.o : $(SRCDIR)/graphvis.c $(INCDIR)/graphvis.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/graphvis.c -o $@ $(LIBS)

$(ODIR)/mem_alloc.o : $(SRCDIR)/mem_alloc.c $(INCDIR)/mem_alloc.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/mem_alloc.c -o $@ $(LIBS)

$(ODIR)/operations.o : $(SRCDIR)/operations.c $(INCDIR)/operations.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/operations.c -o $@ $(LIBS)

$(ODIR)/main.o : $(SRCDIR)/main.c $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/main.c -o $@ $(LIBS)

clean :
	rm -f graphs/*.dot graphs/*.png $(ODIR)/*.o *.exe vgcore.*

clean_g :
	rm -f graphs/*.dot graphs/*.png