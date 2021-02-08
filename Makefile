CC=gcc
CFLAGS=-Wall
LDFLAGS= -I /usr/local/include/fmod -L /usr/local/lib/fmod -lfmod -lncurses -lmenu
TARGET_NAME=Mazety
SRC=src/main.c src/fonctions.c src/menu.c src/labyrinthe.c
DEPS=-I headers/

default: all

all:
	gcc -o $(TARGET_NAME) $(SRC) $(DEPS) $(CFLAGS) $(LDFLAGS)

clean:
	rm $(TARGET_NAME)

run:	all
	LD_LIBRARY_PATH=/usr/local/lib/fmod ./$(TARGET_NAME)

