#include <ncurses.h>
#include <unistd.h>

const size_t DELAY=60000;
char cmd[80];

int x_o;
int y_o;

int t_x(int x){
    return  x-x_o;
}
int t_y(int y){
    return y_o - y;
}

int parabola(int x){
    return (x*x / 4);
}

void plot_function(int (*int_func)(int)){
    int y_n=0;
    for (int i=0; i<COLS; i++){
        y_n = t_y(int_func(t_x(i)));
        if ( y_n <= LINES && y_n >= 0 ){
            mvaddch(y_n, i, 'x');
            refresh();
            usleep(DELAY);
        }
    }
}

char * input_command(int y, int x){
    //move cursor
    mvaddch(y,x,':');
    echo();
    getstr(cmd);
    noecho();
    return(cmd);
}

void run_command(char * user_cmd){
    mvprintw( 4, 4, "%s", user_cmd);
}

void draw_axes(){
    //draw axes
    for (int i=0; i<COLS; i++){
        mvaddch(y_o, i, '#');
    }
    for (int i=0; i < LINES; i++){
        mvaddch(i, x_o, '#');
    }
    refresh();
}

void moveo (int x,int y){
    x_o += x;
    y_o += x;
}


int main(int argc, char** argv){
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    y_o = LINES / 2;
    x_o = COLS / 2;

    char * usr_cmd;

    //user interaction loop
    int in=1;
    while ( in ){
        in = getch();
        switch (in){
            case KEY_UP:
                moveo(0,-1);
                break;
            case KEY_LEFT:
                moveo(0,-1);
                break;
            case KEY_RIGHT:
                moveo(0,-1);
                break;
            case KEY_DOWN:
                moveo(0,-1);
                break;
            case ':': //run command
                usr_cmd = input_command( LINES - 1, 0);
                run_command(usr_cmd);
                break;
            case KEY_F(5) : //refresh
                refresh();
                break;
            case 'q':
                in = 0;
                return 0;
            default :
                break;
        }
    }

    endwin();
}
