CC=gcc
FLAGS=-std=gnu99

LIBOUT=libserialcomm.a

ifdef DEBUG
FLAGS+=-g -O0
endif

ifdef RELEASE
FLAGS+=-O2
endif

ODIR=obj
SDIR=src

OBJS=serialcomm.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

lib: makeodir $(_OBJS)
	ar rcs $(LIBOUT) $(_OBJS)

makeodir:
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c $(FLAGS) -o $@ $<

clean:
	rm -f $(LIBOUT) $(ODIR)/*.o
