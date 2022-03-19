PROJECT = similar_lines
OBJECTS = utilities.o row_parser.o input.o set_maker.o main.o
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

.PHONY: all clean

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(PROJECT)
