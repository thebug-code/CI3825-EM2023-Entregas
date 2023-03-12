CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: prueba

<<<<<<< HEAD
prueba: main.o schedule.o schedule_list.o service.o service_list.o arrival_schedule.o stop_list.o arrival_list.o bus_stop.o utils.o
	$(CC) $(CFLAGS) -o prueba main.o schedule.o schedule_list.o service.o service_list.o arrival_schedule.o stop_list.o arrival_list.o bus_stop.outils.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

schedule.o: schedule.c
	$(CC) $(CFLAGS) -c schedule.c

schedule_list.o: schedule_list.c
	$(CC) $(CFLAGS) -c schedule_list.c

service_list.o: service_list.c
	$(CC) $(CFLAGS) -c service_list.c

service.o: service.c
	$(CC) $(CFLAGS) -c service.c

arrival_schedule.o: arrival_schedule.c
	$(CC) $(CFLAGS) -c arrival_schedule.c

stop_list.o: stop_list.c
	$(CC) $(CFLAGS) -c stop_list.c

arrival_list.o: arrival_list.c
	$(CC) $(CFLAGS) -c arrival_list.c

bus_stop.o: bus_stop.c
	$(CC) $(CFLAGS) -c bus_stop.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm *.o prueba
