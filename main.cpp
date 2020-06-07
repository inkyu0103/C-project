<<<<<<< HEAD
#include "Snake.h"
=======
#include<iostream>
#include<ncurses.h>
#include<clocale>

using namespace std;


void start_screen(){
    setlocale(LC_ALL,"");

    WINDOW * play; 
    WINDOW * score;
    WINDOW * mission;
    
    
    
    int x,y;

    
    initscr();
    curs_set(0); 
    noecho();
    resize_term(140,80);
    mvprintw(1,1,"C++ Project");
    border('*','*','*','*','*','*','*','*');
    



    // play window
    play = newwin(23,46,3,3);
    getmaxyx(play,y,x);
    wborder(play,' ',' ',' ',' ',' ',' ',' ',' ');

    // making map
    // Dynamic allocation
    int** map;
    map = new int*[y];   // row 개만큼 할당 받고, 각 row마다 col개만큼 다시 할당받는다.
    for(int i=0;i<y;i++){
        map[i]=new int[x];
    }

    // mapping  mwv ( y,x)
    for(int row = 0;row< y;row++){
        for(int col = 0; col < x; col++){
            // Wall
            if ((row==0 & col==0) || (row==0 & col == x-1) || (row == y-1 & col == 0)|| (row == y-1 & col == x-1)){
                map[row][col]=2;
                mvwprintw(play,row,col,"x");
            }
            // immune Wall
            else if(row == 0 || col == 0  || col == x-1 || row ==y-1 ){
                map[row][col] = 1;
                mvwprintw(play,row,col,"x");  
            }
            // empty space
            else{
                map[row][col]=0;
                mvwprintw(play,row,col," ");  

            }
        }
    }
    



    
    // score window
    score = newwin(8,20,3,55);
    mvwprintw(score,1,7,"SCORE");
    wborder(score,'x','x','x','x','x','x','x','x');

    // board window
    mission = newwin(8,20,20,55);
    wbkgd(mission,COLOR_PAIR(3));
    mvwprintw(mission,1,7,"BOARD");
    wborder(mission,'x','x','x','x','x','x','x','x');

    
    //update
    refresh();
    wrefresh(play);
    wrefresh(score);
    wrefresh(mission);
    

    
    getch();
    delwin(play);
    endwin();
>>>>>>> 6cb4d60d1a3970c580bf67ff50c8cce651ac9fc5


using namespace std;


int main(){
    snake s;
    s.start();
    
    return 0;



}
