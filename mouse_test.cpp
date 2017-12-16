#include <ncurses.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <tuple>

const unsigned int DELAY = 1000;


enum game_state { RUN, QUIT };
game_state GAME = RUN;

int get_sign (int a){ if (a == 0) return 1; return (a / abs(a)); }

struct Ball{
  Ball() : y(0), x(0) { };
  static const int BALL_SCALE = 5;
  int y, x;
  void moveTo(int oy,int ox){
    int ydiff = oy - y;
    int xdiff = ox - x;
    y = y + get_sign(ydiff) * ceil (double(abs(ydiff)) / (BALL_SCALE * BALL_SCALE));
    x = x + get_sign(xdiff) * ceil (double(abs(xdiff)) / (BALL_SCALE * BALL_SCALE));
//    if (oy < y)
//      y--;
//    else if (oy > y)
//      y++;
//    if (ox < x)
//      x--;
//    else if (ox > x)
//      x++;
  }
};



std::tuple<int,int> get_mousedown_xy(){
  MEVENT m;
  int c = getch();
  if (c == KEY_MOUSE && getmouse(&m) == OK){
    return std::make_tuple(m.y, m.x);
  }
  return std::make_tuple(-1,-1);
}

/*
std::tuple<int,int> get_xy_movement(){
  MEVENT* m = NULL;

  return std::make_tuple(3,3);
}
*/



int main(){
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL); //REPORT_MOUSE_POSITION is not in ALL_MOUSE_EVENTS!!!
  printf("\033[?1003h\n");   //this is the one that tracks every mouse event
  //printf("\e[?1000l\e[?1005l\e[?1015l");
  //printf("\x1b[<0;76;32m");
  noecho(); //if there's an echo, you'll eventually print out characters that close the terminal

  Ball the_ball;
  the_ball.x =  5 + rand()%10;
  the_ball.y =  5 + rand()%10;

  std::tuple<int, int> mouse;

  while( GAME != QUIT ) {
    mouse = get_mousedown_xy();
    if (std::get<0>(mouse) != -1){
      the_ball.moveTo(std::get<0>(mouse),std::get<1>(mouse));
    }

    clear();
    mvaddch(the_ball.y, the_ball.x, 'o');
    refresh();
    usleep( DELAY ); //if I don't add a delay, it crashes. I wonder why?(try gdb thing with separate stdout and stdin)
  }
}
