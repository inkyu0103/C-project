#include "Snake.h"
using namespace std;


//for snakeBody class
snakeBody::snakeBody(){
    x=0;
    y=0;
}



snakeBody::snakeBody(int col, int row){
    x=col;
    y=row;
}


//for snake class
snake::snake(){
    setlocale(LC_ALL,"");

    
    food.x=0;
    food.y=0;
    
    get = 0;
    
    int x,y; // play의 최대 좌표를 받아오기 위한 변수
    

    initscr(); 
    curs_set(0); 
    noecho();
    resize_term(140,80);
    mvprintw(1,1,"C++ Project");
    border('*','*','*','*','*','*','*','*');
    

    // play window
    play = newwin(23,46,3,3);
    getmaxyx(play,y,x);
    wborder(play,'-','-','-','-','-','-','-','-');

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
    mvwprintw(score,1,7,"SOCRE");
    wborder(score,'x','x','x','x','x','x','x','x');

    // board window
    mission = newwin(8,20,20,55);
    wbkgd(mission,COLOR_PAIR(3));
    mvwprintw(mission,1,7,"BOARD");
    wborder(mission,'x','x','x','x','x','x','x','x');

    



    food_char = '*';
    for(int i=0;i<3;i++){
        Rsnake.push_back(snakeBody(24+i,11)); 
    }
    //seg fault

    for(int i=0;i<Rsnake.size();i++){
        mvwprintw(play,Rsnake[i].y,Rsnake[i].x,"o");
    }

    //food를 그린다.
    mvwprintw(play,food.y,food.x,"*");


    
    







    //update
    refresh();
    wrefresh(play);
    wrefresh(score);
    wrefresh(mission);
    

    
    

    socre = 0;

    
    // resize_term(행=row=y ,열=col=x)
   
    
    // max_height = 23 = row=y, max_width 46= col=x;

    // making map
    // map[row][col] = (col,row);

   
    // initail food x,y

 

    //  3,3부터 시작
    //  가로 46 ,세로 23
    //  (3,3) ~ (48,3) 가로 최대
    //  (3,3) ~ (3,25) 세로 최대

    // 뱀 초기 길이 3
    // bodychar --> 뱀을 구성할 문자
    
   

    getch();
    delwin(play);
    endwin();

 
}

snake::~snake(){
    nodelay(stdscr,false);
    getch();
    endwin();
}

void snake::generatefood(){
    while(true){
        int food_x = rand()%max_width+1;
        int food_y = rand()%max_height+1;

        for(int i=0;i<Rsnake.size();i++){
            if(Rsnake[i].x==food_x && Rsnake[i].y == food_y){
                continue;
            }
        }
    }
}

void snake::move(){
    int tmp = getch();
    switch(tmp)
    {
        case KEY_LEFT:
            if (direction !='r')
                direction='l';
            break;

         case KEY_UP:
            if (direction !='d')
                direction='u';
            break;

         case KEY_DOWN:
            if (direction !='u')
                direction='d';
            break;

         case KEY_RIGHT:
            if (direction !='l')
                direction='r';
            break;   
    }

    if(!get)
    {
        mvwprintw(play,Rsnake[Rsnake.size()-1].y,Rsnake[Rsnake.size()-1].x," ");
        refresh();
        Rsnake.pop_back();
    }
    if(direction=='l'){
        Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x-1, Rsnake[0].y));
    }else if (direction=='r'){
        Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x+1,Rsnake[0].y));
    }else if(direction == 'u'){
        Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x,Rsnake[0].y-1));
    }else if(direction=='d'){
        Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x,Rsnake[0].y+1));
    }

    mvwprintw(play,Rsnake[0].y,Rsnake[0].x,"o");
    refresh();



}

void snake::start(){
    while(1){
        move();
    }
}

