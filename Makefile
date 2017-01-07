balls:
	gcc ncurses_balls.c -lncurses -o bounce.exe

default:
	balls

clean:
	rm bounce.exe
