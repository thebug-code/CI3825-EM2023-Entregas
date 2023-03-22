CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: twitter

twitter: main.o user_list.o tweet_list.o hash_table.o pair.o timeline.o screens.o
	$(CC) $(CFLAGS) -o twitter main.o user_list.o tweet_list.o hash_table.o pair.o timeline.o screens.o

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

screens.o: screens.c
	$(CC) $(CFLAGS) -c screens.c

clean:
	rm *.o twitter
