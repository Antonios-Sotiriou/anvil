# Compile all c files to crwindow executable!

CC = gcc
CFLAGS = -Wall -Werror -O2 #-Os -Og -O0 -g
OBJ = anvil
RM = rm
LINKS = -lX11

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

