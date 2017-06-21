CC = g++
OPTIONS = -Wall
EXE = karnaugh
OBJS = main.o table.o

.SUFFIXES: .c .o

all: link

compile: $(OBJS)

.c .o:
	$(CC) $(OPTIONS) $(OBJS) -o $(EXE)

link: compile
	$(CC) $(OPTIONS) $(OBJS) -o $(EXE)

clean:
	rm $(EXE)
	rm $(OBJS)

start: link
	./$(EXE)