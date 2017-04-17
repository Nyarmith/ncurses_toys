#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define DELAY 180000

void print_mod(int dividend, int divisor){
        attron(A_BOLD);
        wprintw(stdscr, "%2d", dividend);
        attroff(A_BOLD);

        attron(A_ITALIC | A_BOLD);
        wprintw(stdscr, " mod ");
        attroff(A_ITALIC | A_BOLD);

        attron(A_BOLD);
        wprintw(stdscr, "%2d ",divisor);
        attroff(A_BOLD);

        attron(A_BLINK | A_DIM);
        wprintw(stdscr, " = ");
        attroff(A_BLINK | A_DIM);

        attron(A_BOLD);
        wprintw(stdscr, "%2d", dividend % divisor);
        attroff(A_BOLD);
}

int main(int argc, char** argv){
    if (argc < 4){
        printf ("usage: %s <start_dividend> <stop_dividend> <start_divisor> <stop_divisor> [multiple]", argv[0]);
        return 0;
    }
    int start_dividend = atoi(argv[1]);
    int stop_dividend  = atoi(argv[2]);
    int start_divisor  = atoi(argv[3]);
    int stop_divisor   = atoi(argv[4]);
    int multiple       = (argc==6) ? atoi(argv[5]) : 1;

    initscr();

    int line = 1;
    while(start_dividend <= stop_dividend){
        move(line, 2);

        int fst = 0;
        //2nd dim
        int divisor_temp = start_divisor;
        while(divisor_temp <= stop_divisor){
            if (fst != 0){
                wprintw(stdscr, "  ");
                attron(A_ALTCHARSET | A_BOLD);
                wprintw(stdscr, "a");
                attroff(A_ALTCHARSET | A_BOLD);
                wprintw(stdscr, " ");
            } else {
                fst = 1;
            }
            print_mod(start_dividend, divisor_temp);
            refresh();
            divisor_temp += multiple;
            usleep( DELAY );

        }

        line++;
        start_dividend += multiple;

        usleep(DELAY);
    }

    mvprintw( LINES - 2, 3, "press any key to exit..");
    getch();
    endwin();

    return 0;
}
