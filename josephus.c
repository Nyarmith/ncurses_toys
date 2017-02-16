#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 30000

#define MAX 256

bool dead[MAX]={0}; /* 1 is dead, 0 is alive*/

int main(int argc, char** argv){
    noecho();
    int k=2; //every Kth person commits peer pressured suicide
    int i;   //generic counter
    int left_alive;
    int number_of_dudes = left_alive = atoi(argv[1]);
    //ok we have everything we need for the problem

    initscr();
    noecho();
    //print all of these out, starting on the second line
    move(2,1);
    for (i=0; i<number_of_dudes; i++){
        addch(' ');
        printw(itoa(i));
    }
    refresh();
    usleep(DELAY);

}
