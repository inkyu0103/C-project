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

    
   
    get = false;
    
    
    initscr(); 
    keypad(stdscr,true);
    nodelay(stdscr,true);
    curs_set(0); 
    noecho();
    resize_term(140,80);
    mvprintw(1,1,"C++ Project");
    border('*','*','*','*','*','*','*','*');

    refresh();


     // play window
    play = newwin(23,46,3,3);

    getmaxyx(play,y,x);
    wborder(play,'x','x','x','x','x','x','x','x');
    wrefresh(play);
     // score window
    score = newwin(8,20,3,55);
    mvwprintw(score,1,7,"SOCRE");
    wborder(score,'x','x','x','x','x','x','x','x');
    wrefresh(score);

    // board window
    mission = newwin(8,20,20,55);
    wbkgd(mission,COLOR_PAIR(3));
    mvwprintw(mission,1,7,"BOARD");
    wborder(mission,'x','x','x','x','x','x','x','x');
    wrefresh(mission);
    

    // making map
    // Dynamic allocation
    
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
    

//seg fault
// snake의 시작점 , 뱀 본체 준비
for(int i=0;i<3;i++){
        Rsnake.push_back(snakeBody(24+i,11)); 
    }

// 맵에 뱀을 그리는 과정
for(int i=0;i<Rsnake.size();i++){
        mvwprintw(play,Rsnake[i].y,Rsnake[i].x,"3");
    }    

//밥을 놓읍시다
    generatefood();

//초기 이동 방향
    direction='l';

//화면 업데이트
    wrefresh(play);
// 자잘한 변수들 (다음 단계에서 사용할 것들)
    food_char = '*';
    socre = 0;


    // resize_term(행=row=y ,열=col=x)
    // max_height = 23 = row=y, max_width 46= col=x;
    // map[row][col] = (col,row);


    //  3,3부터 시작
    //  가로 46 ,세로 23
    //  (3,3) ~ (48,3) 가로 최대
    //  (3,3) ~ (3,25) 세로 최대
    // 뱀 초기 길이 3
    // bodychar --> 뱀을 구성할 문자
    
   

   

 
}

snake::~snake(){
    nodelay(stdscr,false);
    getch();
    endwin();
}

void snake::generatefood(){
    // 밥을 줄까 독을 줄까 결정해주는 rand
    while(true){
        int food_x = rand()%x+2;
        int food_y = rand()%y+2;
        for(int i=0;i<Rsnake.size();i++){
            if(Rsnake[i].x==food_x && Rsnake[i].y == food_y){
                continue;
            }
        }
        food.x = food_x;
        food.y = food_y;
        break;
    }


    mvwprintw(play,food.y,food.x,"+"); // 음식 추가
    wrefresh(play);  // 음식 업데이트
}


bool snake::collision(){

    // 벽에 부딪힌 경우
    if(map[Rsnake[0].y][Rsnake[0].x]==1){
        return true;
    }
    
    //뱀이 자기를 물은 경우
    for(int i=2;i<Rsnake.size();i++){
        if(Rsnake[0].x == Rsnake[i].x && Rsnake[0].y == Rsnake[i].y){
            return true;
        }
    }

    //밥을 먹은 경우

    if(Rsnake[0].x==food.x && Rsnake[0].y == food.y){
        get = true;
        generatefood();
        socre +=10;

        // board에 점수 올라 가는 것 구현해야함

    }else{
        get = false;
    }
    return false;

}


void snake::move(){

    // 키를 입력 받습니다.
    int key = getch();

    switch(key){
        case KEY_LEFT:
			if(direction =='r'){
                flag =1;
                break;
            }
				direction='l';
			break;
		
        case KEY_UP:
			if(direction=='d'){
                flag=1;
                break;
            }
			direction='u';
			break;
		
        
        case KEY_DOWN:
			if(direction =='u'){
                flag = 1;
                break;
            }
			direction='d';
			break;
		
        
        case KEY_RIGHT:
			if(direction =='l'){
                flag =1 ;
                break;
            }
			direction='r';
			break;
		
    }

    if(!get){
		mvwprintw(play,Rsnake[Rsnake.size()-1].y,Rsnake[Rsnake.size()-1].x," ");
        map[Rsnake[Rsnake.size()-1].y][Rsnake[Rsnake.size()-1].x] = 0;
		Rsnake.pop_back();
        wrefresh(play);
        }
    if(direction=='l')
	{
		Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x-1,Rsnake[0].y));
        if(map[Rsnake[0].y][Rsnake[0].x]==1){
            flag = 1;
        }
	}else if(direction=='r'){
		Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x+1,Rsnake[0].y));
        if(map[Rsnake[0].y][Rsnake[0].x]==1){
            flag = 1;
        }

	}else if(direction=='u'){
		Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x,Rsnake[0].y-1));
        if(map[Rsnake[0].y][Rsnake[0].x]==1){
            flag = 1;

        }

	}else if(direction=='d'){
		Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x,Rsnake[0].y+1));
        if(map[Rsnake[0].y][Rsnake[0].x]==1){
            flag = 1;
        }
     
	}
	    mvwprintw(play,Rsnake[0].y,Rsnake[0].x,"3");
        map[Rsnake[0].y][Rsnake[0].x]=3;
        wrefresh(play);
    
}

void snake::start(){
    
    while(1){
        if(collision()){
            mvwprintw(play,12,36,"gameOVer");
            break;
        }
        move();
        if (flag==1){
            break;
        }
        //flag initialize
        flag =0;
        //usleep 값에따라 지렁이 속도가 달라집니다.
        usleep(90000);
        
    }

}
