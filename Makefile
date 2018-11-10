CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g -I include
SRC = src/map.c

.PHONY: all
all:
	$(CC) $(CFLAGS) $(SRC) -o main

clean:
	$(RM) main
