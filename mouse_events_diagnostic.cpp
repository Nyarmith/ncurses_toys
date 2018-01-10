#include <ncurses.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <tuple>


int max_y, max_x;

void log_bstate(mmask_t bstate){
  static int y=5;
  static int x=2;
  //do stuff
  //draw the bstate
  if(bstate & BUTTON1_PRESSED){
    mvprintw(y,x,"BUTTON1_PRESSED"); ++y; }
  if(bstate & BUTTON1_RELEASED){
    mvprintw(y,x,"BUTTON1_RELEASED"); ++y; }
  if(bstate & BUTTON1_CLICKED){
    mvprintw(y,x,"BUTTON1_CLICKED"); ++y; }
  if(bstate & BUTTON1_DOUBLE_CLICKED){
    mvprintw(y,x,"BUTTON1_DOUBLE_CLICKED"); ++y; }
  if(bstate & BUTTON1_TRIPLE_CLICKED){
    mvprintw(y,x,"BUTTON1_TRIPLE_CLICKED"); ++y; }

  if (y > max_y) { y = 5; }

  if(bstate & BUTTON2_PRESSED){
    mvprintw(y,x,"BUTTON2_PRESSED"); ++y; }
  if(bstate & BUTTON2_RELEASED){
    mvprintw(y,x,"BUTTON2_RELEASED"); ++y; }
  if(bstate & BUTTON2_CLICKED){
    mvprintw(y,x,"BUTTON2_CLICKED"); ++y; }
  if(bstate & BUTTON2_DOUBLE_CLICKED){
    mvprintw(y,x,"BUTTON2_DOUBLE_CLICKED"); ++y; }
  if(bstate & BUTTON2_TRIPLE_CLICKED){
    mvprintw(y,x,"BUTTON2_TRIPLE_CLICKED"); ++y; }

  if (y > max_y) { y = 5; }

  if(bstate & BUTTON3_PRESSED){
    mvprintw(y,x,"BUTTON3_PRESSED"); ++y; }
  if(bstate & BUTTON3_RELEASED){
    mvprintw(y,x,"BUTTON3_RELEASED"); ++y; }
  if(bstate & BUTTON3_CLICKED){
    mvprintw(y,x,"BUTTON3_CLICKED"); ++y; }
  if(bstate & BUTTON3_DOUBLE_CLICKED){
    mvprintw(y,x,"BUTTON3_DOUBLE_CLICKED"); ++y; }
  if(bstate & BUTTON3_TRIPLE_CLICKED){
    mvprintw(y,x,"BUTTON3_TRIPLE_CLICKED"); ++y; }
  if(bstate & BUTTON3_PRESSED){

  if (y > max_y) { y = 5; }

    mvprintw(y,x,"BUTTON4_PRESSED"); ++y; }
  if(bstate & BUTTON4_RELEASED){
    mvprintw(y,x,"BUTTON4_RELEASED"); ++y; }
  if(bstate & BUTTON4_CLICKED){
    mvprintw(y,x,"BUTTON4_CLICKED"); ++y; }
  if(bstate & BUTTON4_DOUBLE_CLICKED){
    mvprintw(y,x,"BUTTON4_DOUBLE_CLICKED"); ++y; }
  if(bstate & BUTTON4_TRIPLE_CLICKED){
    mvprintw(y,x,"BUTTON4_TRIPLE_CLICKED"); ++y; }

  if (y > max_y) { y = 5; }

  if(bstate & BUTTON_SHIFT){
    mvprintw(y,x,"BUTTON_SHIFT"); ++y; }
  if(bstate & BUTTON_CTRL){
    mvprintw(y,x,"BUTTON_CTRL"); ++y; }
  if(bstate & BUTTON_ALT){
    mvprintw(y,x,"BUTTON_ALT"); ++y; }
  if(bstate & REPORT_MOUSE_POSITION){
    mvprintw(y,x,"REPORT_MOUSE_POSITION"); ++y; }
//  if(bstate & ALL_MOUSE_EVENTS){
//    mvprintw(y,x,"ALL_MOUSE_EVENTS"); ++y; }

  if (y > max_y) { y = 5; }

}

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

  getmaxyx(stdscr, max_y, max_x);


  int c;
  MEVENT m;
  do {
    c = getch();
    if (c == KEY_MOUSE && getmouse(&m) == OK){
      mvprintw(2, 3, "                                        ");
      mvprintw(2, 3, "y:%d , x:%d -- bstate: 0x%08X", m.y, m.x, m.bstate);

      log_bstate(m.bstate);

      refresh();
    }
  } while (c != 'q');
  endwin();
}
