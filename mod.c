#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define DELAY 300000

int main(int argc, char** argv){
    if (argc < 4){
        printf ("usage: %s <number> <startno> <endno> [multiple]", argv[0]);
        return 0;
    }
    int number = atoi(argv[1]);
    int startno = atoi(argv[2]);
    int endno = atoi(argv[3]);
    int multiple = (argc==5) ? atoi(argv[4]) : 1;

    initscr();
    int line = 1;
    while(startno <= endno){
        move(line, 2);

        attron(A_BOLD);
        wprintw(stdscr, "%d", number);
        attroff(A_BOLD);

        attron(A_ITALIC | A_BOLD);
        wprintw(stdscr, " mod ");
        attroff(A_ITALIC | A_BOLD);

        attron(A_BOLD);
        wprintw(stdscr, "%d",startno);
        attroff(A_BOLD);

        attron(A_BLINK | A_DIM);
        wprintw(stdscr, " = ");
        attroff(A_BLINK | A_DIM);

        attron(A_BOLD);
        wprintw(stdscr, "%d", number % startno);
        attroff(A_BOLD);

        refresh();

        line++;
        startno += multiple;

        usleep(DELAY);
    }

    mvprintw( LINES - 2, 3, "press any key to exit..");
    getch();
    endwin();

    return 0;
}
