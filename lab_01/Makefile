CC := gcc
KEYS := -g -Wall -Werror -Wredundant-decls -std=c99 -Wfloat-conversion -Wfloat-equal -Wpedantic -Wextra -Wvla
ODIR := ./out
SRCDIR := ./src
INCDIR := ./inc
OBJS := $(ODIR)/readme.o $(ODIR)/operations.o
LIBS := -Iinc

all : app.exe

app.exe : $(OBJS) $(ODIR)/main.o
	$(CC) $^ -o $@ $(LIBS)

$(ODIR)/readme.o : $(SRCDIR)/readme.c $(INCDIR)/readme.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/readme.c -o $@ $(LIBS)

$(ODIR)/operations.o : $(SRCDIR)/operations.c $(INCDIR)/operations.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/operations.c -o $@ $(LIBS)

$(ODIR)/main.o : $(SRCDIR)/main.c $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/main.c -o $@ $(LIBS)

clean :
	rm -f $(ODIR)/*.o *.exe
