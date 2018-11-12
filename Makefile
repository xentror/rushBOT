CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g -I include
SRC = $(wildcard src/*.c)
CFLAGS += -lm -lpthread -Llib -lSDL2 -lSDL2_image

.PHONY: all
all:
	$(CC) $(CFLAGS) $(SRC) -o Epic-Age-Of-Dark-Battle-Of-Tank

clean:
	$(RM) Epic-Age-Of-Dark-Battle-Of-Tank

