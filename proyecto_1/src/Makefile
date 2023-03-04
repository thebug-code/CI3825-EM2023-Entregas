CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: prueba

prueba: main.o schedule.o schedule_list.o utils.o service.o service_list.o
	$(CC) $(CFLAGS) -o prueba main.o schedule.o schedule_list.o service.o service_list.o utils.o

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

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm *.o prueba
