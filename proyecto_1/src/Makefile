# Compiler to use
CC = gcc
# Compiler flags
CFLAGS = -Wall -pedantic
# Libraries to link with
LDLIBS = -lm

# Object files to link together
OBJ = schedule.o schedule_list.o service.o arrival_list.o arrival_schedule.o bus_stop.o service_list.o utils.o stop_list.o main.o

# Default target
all: simutransusb

# Target for final program
simutransusb: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o simutransusb

# Compile schedule object file
schedule.o: schedule.c schedule.h
	$(CC) $(CFLAGS) -c schedule.c

# Compile schedule list object file
schedule_list.o: schedule_list.c schedule_list.h
	$(CC) $(CFLAGS) -c schedule_list.c

# Compile service object file
service.o: service.c service.h
	$(CC) $(CFLAGS) -c service.c

# Compile arrival list object file
arrival_list.o: arrival_list.c arrival_list.h
	$(CC) $(CFLAGS) -c arrival_list.c

# Compile arrival schedule object file
arrival_schedule.o: arrival_schedule.c arrival_schedule.h
	$(CC) $(CFLAGS) -c arrival_schedule.c

# Compile bus stop object file
bus_stop.o: bus_stop.c bus_stop.h
	$(CC) $(CFLAGS) -c bus_stop.c

# Compile service list object file
service_list.o: service_list.c service_list.h
	$(CC) $(CFLAGS) -c service_list.c

# Compile utils object file
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# Compile stop list object file
stop_list.o: stop_list.c stop_list.h
	$(CC) $(CFLAGS) -c stop_list.c

# Compile main object file
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Clean up object files and final program
clean:
	rm -f *.o simutransusb

