# Compiler to use
CC = gcc
# Compiler flags
# -Wall: Turn on all warnings
#  -pedantic: Turn on pedantic warnings
CFLAGS = -Wall -pedantic
# Libraries to link with
LDLIBS = -lm

# Object files to link together
OBJ = main.o cli_parser.o directory_parser.o

# Default target
all: fameChecker

# Target for final program
fameChecker: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o fameChecker

# Compile cli_parser object file
cli_parser.o: cli_parser.c cli_parser.h
	$(CC) $(CFLAGS) -c cli_parser.c

# Compile directory_parser object file
directory_parser.o: directory_parser.c directory_parser.h
	$(CC) $(CFLAGS) -c directory_parser.c

# Compile main object file
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Clean up object files and final program
clean:
	rm -f *.o fameChecker

