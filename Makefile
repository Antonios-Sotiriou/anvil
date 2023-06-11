# Compile all c files to anvil executable!

CC = gcc
CFLAGS = -Werror -g#-O2 -Os -Og -O0
OBJ = anvil
RM = rm
LINKS = -lX11 -lm
INTRINSICS = #-msse4.2#-mavx2 #-mavx512f #-msse4.2 #-msse #-msse2 #-msse2avx #-msse3 -msse4 #-msse4.1 -msse4a -msse5 -msseregparm -mssse3 -msse-check=warning -msse2avx -march=CPU,i7 
FILENAME = draw_functions.c

install:
	./install.sh;

uninstall:
	sudo apt remove libx11-dev;

all:
	$(CC) $(CFLAGS) $(INTRINSICS) main.c locale.c matrices.c vectors_math.c clipping.c obj_parser.c draw_functions.c general_functions.c exec_time.c lighting.c camera.c quaternions.c shadowmap.c logging.c -o $(OBJ) $(LINKS);

exec:
	./$(OBJ)

assembly:
	$(CC) -S $(FILENAME);

clean:
	sudo apt autoremove -y;

