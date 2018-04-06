CC=gcc
CFLAGS=-Wall
LDFLAGS=-lncurses
TARGET_NAME=Mazety.bin
SRC=src/labyseulModify.c src/fonctions.c
DEPS=-I headers/

default: all

all:
	gcc -o $(TARGET_NAME) $(SRC) $(DEPS) $(CFLAGS) $(LDFLAGS)

clean:
	rm $(TARGET_NAME)

run:	all
	./$(TARGET_NAME)
