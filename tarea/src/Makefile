CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: sustituir

sustituir: main.o user_list.o tweet_list.o hash_table.o pair.o timeline.o main_screen.o
	$(CC) $(CFLAGS) -o sustituir main.o user_list.o tweet_list.o hash_table.o pair.o timeline.o main_screen.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

user_list.o: user_list.c
	$(CC) $(CFLAGS) -c user_list.c

tweet_list.o: tweet_list.c
	$(CC) $(CFLAGS) -c tweet_list.c

hash_table.o: hash_table.c
	$(CC) $(CFLAGS) -c hash_table.c

pair.o: pair.c
	$(CC) $(CFLAGS) -c pair.c

timeline.o: timeline.c
	$(CC) $(CFLAGS) -c timeline.c

main_screen.o: main_screen.c
	$(CC) $(CFLAGS) -c main_screen.c

clean:
	rm *.o sustituir
