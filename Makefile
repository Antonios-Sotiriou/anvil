# Compile all c files to crwindow executable!

CC = gcc
CFLAGS = -Werror -g # -O2 -Os -Og -O0
OBJ = anvil
RM = rm
LINKS = -lX11 -lm

install:
	./install.sh;

uninstall:
	sudo apt remove libx11-dev;

all:
	$(CC) $(CFLAGS) main.c locale.c matrices.c vectors_math.c clipping.c test_shapes.c obj_parser.c draw_functions.c -o $(OBJ) $(LINKS);

exec:
	./anvil

clean:
	sudo apt autoremove -y;

