# Written by Diogo Tartarotti for CSC 161 Fall 2021 at Grinnell College
# Disable the use of implicit build rules
.SUFFIXES:


CC = clang
CPPFLAGS =
CFLAGS += -Wall -Werror -std=c11 -fsanitize=address
LDFLAGS = -fsanitize=address 

all: solve

solve: solve.o path.o maze.o queue.o
	$(CC) $(LDFLAGS) -o $@ $^

# Library object files
solve.o: solve.c position.h path.h queue.h maze.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

path.o: path.c position.h path.h 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

maze.o: maze.c position.h maze.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

queue.o: queue.c queue.h path.h position.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	rm -f solve *.o *~ core*
