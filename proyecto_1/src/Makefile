CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: prueba

prueba: main.o arrival_schedule.o stop_list.o arrival_list.o bus_stop.o load_file.o
	$(CC) $(CFLAGS) -o prueba main.o arrival_schedule.o stop_list.o arrival_list.o bus_stop.o load_file.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

arrival_schedule.o: arrival_schedule.c
	$(CC) $(CFLAGS) -c arrival_schedule.c

stop_list.o: stop_list.c
	$(CC) $(CFLAGS) -c stop_list.c

arrival_list.o: arrival_list.c
	$(CC) $(CFLAGS) -c arrival_list.c

bus_stop.o: bus_stop.c
	$(CC) $(CFLAGS) -c bus_stop.c

load_file.o: load_file.c
	$(CC) $(CFLAGS) -c load_file.c

clean:
	rm *.o prueba