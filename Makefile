all: sdlanim

sdlanim:	main.c
	gcc main.c fonction.c `sdl-config --cflags --libs` -lm -lSDL_ttf -g -o Test

clean:
	rm Test
