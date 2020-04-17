OUTDIR = .out
CC	= gcc
CFLAGS	=-g -Wall

SRCS = $(wildcard ./*.c)
OBJS = $(patsubst ./%.c, $(OUTDIR)/%.o, $(SRCS)) 
EXE = snake

all: $(OUTDIR) $(EXE)
	clang-format -i *.[ch]
	
$(OUTDIR):
	mkdir $(OUTDIR)

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean run format

run:
	./$(EXE)

clean:
	rm -f $(OUTDIR)/* ./$(EXE)
	rmdir ./$(OUTDIR)