default:
	gcc ncurses_balls.c -lncurses -o bounce.exe

clean:
	rm bounce.exe
