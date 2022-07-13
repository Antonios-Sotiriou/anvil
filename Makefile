# Compile all c files to crwindow executable!

CC = gcc
CFLAGS = -Wall -O2 -g #-Os -Og -O0
OBJ = anvil
RM = rm
LINKS = -lX11 -lm

install:
	./install.sh;

uninstall:
	sudo apt remove libx11-dev;

all:
	$(CC) $(CFLAGS) main.c locale.c -o $(OBJ) $(LINKS);

exec:
	./anvil

clean:
	sudo apt autoremove -y;

