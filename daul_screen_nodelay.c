#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#define DELAY 65000



//idea: left window controlled with wasd, right window controlled with arrow keys


//the snake is a doubly-linked list
typedef struct node{
  int x;
  int y;
  struct node* next;
  struct node* prev;
} node_t;

//nodes are just on the screen
node_t * left = NULL;
node_t * right  = NULL;



void move_node(int dx, int dy, node_t* n, int max_x, int max_y){
  int new_x = n->x + dx;
  int new_y = n->y + dy;
  if (new_x < 0 || new_x >max_x || new_y < 0 || new_y > max_y) {
    n->x = max_x / 2;
    n->y = max_y / 2;
  } else {
    n->x = new_x;
    n->y = new_y;
  }
}

void init_nodes(int lmy, int lmx, int rmy, int rmx);
void handle_key(int c);

int main(){

  int max_y, max_x;
  WINDOW* lwin;
  WINDOW* rwin;
  //ncurses init stuff
  initscr();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, max_y, max_x);


  //I probably startmaking new windows here
  lwin = newwin(max_y / 2,max_x / 2,0,0);
  rwin = newwin(max_y / 2, max_x / 2, max_y / 2, max_x / 2);


  //init the nodes
  init_nodes();

  int last_left_key = KEY_LEFT;
  int last_right_key = 'a';
  int left_input ='e';
  int right_input='e';

  //our loop is fairly simple, we could have handles input a number
  //of different ways, such as a separate function to handle a global flag
  //or just a handle_input that returns a struct with the dx, dy vals
  while(left_input != 'p' && right_input != 'p') {

    input = getch();
    if (input != ERR)   //ERR is returned if we don't provide any input
      last_key = input;  //if the user hits any other key it becomes last_key!
    handle_key(last_left_key, last_right_key);


    clear();    //draws screen
    wrefresh();
    //refresh();

    usleep(DELAY);  //u = mu = sleep for microseconds

  }
  endwin();
}

void handle_key(int c1, int c2, int max_y, int max_x){
  switch(c1){
    case KEY_UP:    //right window
      move_node(0,-1,right,max_y/2, max_x/2);
      break;
    case KEY_LEFT:
      move_snek(-1,0,right, );
      break;
    case KEY_RIGHT:
      move_snek(1,0,right, ); //TODO: Continue here
      break;
    case KEY_DOWN:
      move_snek(0,1);
  }
  switch(c2){
    case 'w':      //left window
      move_snek(0,-1);
      break;
    case 'a':
      move_snek(-1,0);
      break;
    case 's':
      move_snek(1, 0);
      break;
    case 'd':
      move_snek(0,1);
      break;
  }
}

void init_nodes(){
  left   =  malloc(sizeof(node_t));
  right  =  malloc(sizeof(node_t));
  left->x  = max_x/2;
  left->y  = max_y/2;
  right->x = max_x/2;
  right->y = max_y/2;
  snek_back ->x = max_x/2 + 1;
  snek_back ->y = max_x/2;
  snek_front->prev = NULL; snek_back->next = NULL;
  //point to each other
  snek_front->next = snek_back; snek_back->prev = snek_front;
}
