all: sdl_jstest.c
	cc --std=c99 -Wall -lSDL2 \
	-o sdl-jstest sdl_jstest.c

debug: sdl_jstest.c
	cc --std=c99 -Wall -lSDL2 \
	-fsanitize=undefined \
	-fsanitize=address \
	-o sdl-jstest -g sdl_jstest.c

run: sdl-jstest
	./sdl-jstest

clean:
	rm -rf sdl-jstest sdl-jstest.dSYM
