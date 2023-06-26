# Compile all c files to anvil executable!

CC = gcc
CFLAGS = -Werror -g -msse4.2 # -O2 -Os -Og -O0
OBJ = anvil
RM = rm
LINKS = -lX11 -lm
INTRINSICS = #-msse4.2 -msse -msse2 -msse2avx -msse3 -msse4 -msse4.1 -msse4a -msse5 -msseregparm -mssse3 -msse-check=warning -msse2avx -march=CPU,i7 
FILENAME = main.c

install:
	./install.sh;

uninstall:
	sudo apt remove libx11-dev;

sc:
	$(CC) $(CFLAGS) main.c locale.c matrices.c vectors_math.c clipping.c obj_parser.c scanline.c drawline.c general_functions.c exec_time.c lighting.c camera.c quaternions.c shadowmap.c grfk_pipeline.c kinetics.c world_objects.c logging.c -o $(OBJ) $(LINKS);

ed:
	$(CC) $(CFLAGS) main.c locale.c matrices.c vectors_math.c clipping.c obj_parser.c edgefunc.c drawline.c general_functions.c exec_time.c lighting.c camera.c quaternions.c shadowmap.c grfk_pipeline.c kinetics.c world_objects.c logging.c -o $(OBJ) $(LINKS);

exec:
	./$(OBJ)

assembly:
	$(CC) -S $(FILENAME);

clean:
	sudo apt autoremove -y;

