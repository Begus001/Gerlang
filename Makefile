CC = /bin/cc
CFLAGS = -O0 -Wall -Wextra -std=gnu17 -pedantic -I.

SRCS = main.c
BIN = ger

build:
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN)

run: build
	./$(BIN)
