CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: sustituir

sustituir: main.o user_list.o tweet_list.o
	$(CC) $(CFLAGS) -o sustituir main.o user_list.o tweet_list.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

user_list.o: user_list.c
	$(CC) $(CFLAGS) -c user_list.c

tweet_list.o: tweet_list.c
	$(CC) $(CFLAGS) -c tweet_list.c

clean:
	rm *.o sustituir

