CC=gcc
CFLAGS=-Wall
LDFLAGS=-lfmod -L lib-ext/fmodstudioapi11004linux/api/lowlevel/lib/x86_64/ -lncurses -lmenu
TARGET_NAME=Mazety.bin
SRC=src/main.c src/fonctions.c src/Menu.c
DEPS=-I headers/

default: all

all:
	gcc -o $(TARGET_NAME) $(SRC) $(DEPS) $(CFLAGS) $(LDFLAGS)

clean:
	rm $(TARGET_NAME)

run:	all
	LD_LIBRARY_PATH=lib-ext/fmodstudioapi11004linux/api/lowlevel/lib/x86_64/ ./$(TARGET_NAME)

