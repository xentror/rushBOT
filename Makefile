CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g -I include
SRC = $(wildcard src/*.c)

.PHONY: all
all:
	$(CC) $(CFLAGS) $(SRC) -o main

clean:
	$(RM) main
