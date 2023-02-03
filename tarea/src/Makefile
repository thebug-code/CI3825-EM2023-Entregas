CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: sustituir

sustituir: main.o user_list.o tweet_list.o hash_table.o
	$(CC) $(CFLAGS) -o sustituir main.o user_list.o tweet_list.o hash_table.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

user_list.o: user_list.c
	$(CC) $(CFLAGS) -c user_list.c

tweet_list.o: tweet_list.c
	$(CC) $(CFLAGS) -c tweet_list.c

hash_table.o: hash_table.c
	$(CC) $(CFLAGS) -c hash_table.c

clean:
	rm *.o sustituir

