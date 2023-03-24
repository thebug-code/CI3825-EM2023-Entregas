# Compiler to use
CC = gcc
# Compiler flags
CFLAGS = -Wall -pedantic
# Libraries to link with
LDLIBS = -lm

# Object files to link together
OBJ = bus_departure_time.o bus_departure_time_list.o service_characterization.o service_characterization_list.o arrival_list.o arrival_schedule.o bus_stop.o  utils.o stop_list.o main.o

# Default target
all: simutransusb

# Target for final program
simutransusb: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o simutransusb

# Compile schedule object file
bus_departure_time.o: bus_departure_time.c bus_departure_time.h
	$(CC) $(CFLAGS) -c bus_departure_time.c

# Compile schedule list object file
bus_departure_time_list.o: bus_departure_time_list.c bus_departure_time_list.h
	$(CC) $(CFLAGS) -c bus_departure_time_list.c

# Compile service object file
service_characterization.o: service_characterization.c service_characterization.h
	$(CC) $(CFLAGS) -c service_characterization.c

# Compile service list object file
service_characterization_list.o: service_characterization_list.c service_characterization_list.h
	$(CC) $(CFLAGS) -c service_characterization_list.c

# Compile arrival list object file
arrival_list.o: arrival_list.c arrival_list.h
	$(CC) $(CFLAGS) -c arrival_list.c

# Compile arrival schedule object file
arrival_schedule.o: arrival_schedule.c arrival_schedule.h
	$(CC) $(CFLAGS) -c arrival_schedule.c

# Compile bus stop object file
bus_stop.o: bus_stop.c bus_stop.h
	$(CC) $(CFLAGS) -c bus_stop.c

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

