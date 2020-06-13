#include "Snake.h"
#include <time.h>
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
gatePos::gatePos(){
    g_x = 0;
    g_y = 0;
}

gatePos::gatePos(int g_col,int g_row){
    g_x = g_col;
    g_y = g_row;
}


//for snake class
snake::snake(){
    setlocale(LC_ALL,"");
    
    // 뭔가 먹었니?
    get = false;
    
    // 독 먹었니?
    poi = false;

    // configurtaion initial size
    max_height = 23;
    max_width = 46;
    
    
    initscr(); 
    start_color();

    // 색깔 사용
    init_pair(1,COLOR_RED,COLOR_WHITE);

    keypad(stdscr,true);
    nodelay(stdscr,true);
    curs_set(0); 
    noecho();
    resize_term(140,80);
    mvprintw(1,1,"C++ Project");
    border('*','*','*','*','*','*','*','*');

    refresh();


     // play window
    play = newwin(max_height,max_width,3,3);

    getmaxyx(play,y,x);
    wborder(play,'x','x','x','x','x','x','x','x');
    wrefresh(play);
     // score window
    score = newwin(8,20,3,55);
    //  mission window
    mission = newwin(8,20,13,55);
    point  = 0;
    food_cnt = 0;
    poison_cnt = 0;
    gate_cnt = 0;
    body_length = INIT_LENGTH + food_cnt - poison_cnt;
    speed_interval = 15000;
    current_speed = INIT_SPEED;
    mvwprintw(score,1,4,"Score Board");
    mvwprintw(score,2,3,"B : ");
    mvwprintw(score,3,3,"+ : ");
    mvwprintw(score,4,3,"- : ");
    mvwprintw(score,5,3,"G : ");
    wborder(score,'|','|','-','-','-','-','|','|');
    // wborder(score,'x','x','x','x','x','x','x','x');
    wrefresh(score);

    mvwprintw(mission,1,5,"Mission");
    mvwprintw(mission,2,3,"B : ( )");
    mvwprintw(mission,3,3,"+ : ( )");
    mvwprintw(mission,4,3,"- : ( )");
    mvwprintw(mission,5,3,"G : ( )");
    wborder(mission,'|','|','-','-','-','-','|','|');
    wrefresh(mission);
    // score window
    // score = newwin(8,20,20,55);
    // wbkgd(score,COLOR_PAIR(3));
    // mvwprintw(score,1,7,"Score Board");
    // wrefresh(score);
    // wborder(score,'','-','-','|','|','-','-','-');
    // mission window
   

    // making map
    // Dynamic allocation
    
    map = new int*[y];   // row 개만큼 할당 받고, 각 row마다 col개만큼 다시 할당받는다.
    for(int i=0;i<y;i++){
        map[i]=new int[x];
    }

    // mapping  mwv (y,x)
    for(int row = 0;row< y;row++){
        for(int col = 0; col < x; col++){
            // Wall
            if ((row==0 && col==0) || (row== 0 && col == x-1) || (row == y-1 && col == 0)|| (row == y-1 && col == x-1)){
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
        mvwprintw(play,Rsnake[i].y,Rsnake[i].x,"O");
        map[Rsnake[i].y][Rsnake[i].x] = 3;
    }    

//밥과 독을 놓읍시다.
    generatefood();
    generatepoison();

//초기 이동 방향
    direction='l';

//화면 업데이트
    wrefresh(play);
// 자잘한 변수들 (다음 단계에서 사용할 것들)


    // resize_term(행=row=y ,열=col=x)
    // max_height = 23 = row=y, max_width 46= col=x;
    // map[row][col] = (col,row);


    //  3,3부터 시작
    //  가로 46 ,세로 23
    //  (3,3) ~ (48,3) 가로 최대
    //  (3,3) ~ (3,25) 세로 최대
    // 뱀 초기 길이 3
    
}

snake::~snake(){
    nodelay(stdscr,false);
    getch();
    endwin();
}

// 독을 만드는 과정
void snake::generatepoison(){
    while(true){
        int poison_x = rand()%(x-4)+2;
        int poison_y = rand()%(y-4)+2;

        // 독을 만들었는데, 그게 벽 위라면? 다시 만들어라
        if ( map[poison_y][poison_x] == 1 ||map[poison_y][poison_x] == 2 ){
            continue;
        }

        for(int i=0;i<Rsnake.size();i++){
            if(Rsnake[i].x==poison_x && Rsnake[i].y == poison_y){
                continue;
            }
        }
        poison.x = poison_x;
        poison.y = poison_y;

        //이게 밥이나 독약을 map 배열에서 표시를 해야한다고 되어있긴 한데, 제 능력으로는 계속 segmentation fault가 나서 일단 보류했습니다.
        //map[food.y][food.x] = 4;
        break;
    }

    mvwprintw(play,poison.y,poison.x,"-"); // 독 추가
    wrefresh(play);  // 독 업데이트
}




void snake::generatefood(){
    
    while(true){
        int food_x = rand()%(x-4)+2;
        int food_y = rand()%(y-4)+2;
           if ( map[food_y][food_x] == 1 ||map[food_y][food_x] == 2 ){
            continue;
        }


        for(int i=0;i<Rsnake.size();i++){
            if(Rsnake[i].x==food_x && Rsnake[i].y == food_y){
                continue;
            }
        }
        food.x = food_x;
        food.y = food_y;
        
        //map[food.y][food.x] = 4;
        break;
    }

    mvwprintw(play,food.y,food.x,"+"); // 음식 추가
    wrefresh(play);  // 음식 업데이트

}


bool snake::collision(){

   
    // 몸 길이가 2 이하인 경우
    // 뱀 길이 설정, 좌표설정, 위치설정

    // 벽에 부딪힌 경우
    if(map[Rsnake[0].y][Rsnake[0].x]==1){
        // TODO :: 반대 게이트로 나오게
        return true;
    }
    
    //뱀이 자기를 물은 경우
    for(int i=2;i<Rsnake.size();i++){
        if(Rsnake[0].x == Rsnake[i].x && Rsnake[0].y == Rsnake[i].y){
            return true;
        }
    }

    //독을 먹은 경우
    if((Rsnake[0].x==poison.x) && (Rsnake[0].y == poison.y)){

        generatepoison();
        poison_cnt+=1;
        // point -=10;
        body_length = INIT_LENGTH + food_cnt - poison_cnt;
        current_speed += speed_interval;
       
        if (body_length<3){
            return true;
        }
        mvwprintw(score,4,10,"%d",poison_cnt);
        mvwprintw(score,2,10,"%d",body_length);
        wrefresh(score);
        mvwprintw(play,Rsnake[Rsnake.size()-1].y,Rsnake[Rsnake.size()-1].x," ");
        map[Rsnake[Rsnake.size()-1].y][Rsnake[Rsnake.size()-1].x]=0;
        Rsnake.pop_back();
        usleep(current_speed);

    }


    //밥을 먹은 경우
    if((Rsnake[0].x==food.x) && (Rsnake[0].y == food.y)){
        //map[food.y][food.x] = 3;

        generatefood(); 
        get = true;
        food_cnt+=1;
        // point +=10;
        body_length = INIT_LENGTH + food_cnt - poison_cnt;
        current_speed -= speed_interval;
        // mvwprintw(score,2,16,"%d",point);
        mvwprintw(score,2,10,"%d",body_length);
        mvwprintw(score,3,10,"%d",food_cnt);
        wrefresh(score);
    // board에 점수 올라 가는 것 구현해야함
        usleep(current_speed);
        return false;

    }
    
    else{
       get=false;
    }

    
    return false;

}

void snake::make_gate(){
    srand((unsigned int)time(0));
    int firstLayer = rand()%4;
    int secondLayer = rand()%4;

    while (1)
    {
        switch ((enum LayerType)firstLayer)
        {
        case G1:
            fgate.g_y = 1 + rand()%(max_width-4);    //gate1(0,rand)
            break;
        case G2:
            fgate.g_x = 1 + rand()%(max_height-4);    //gate2(rand,0)
            break;
        case G3:
            fgate.g_x = max_height-1;
            fgate.g_y = 1 + rand()%(max_width-4);    //gate3(max,rand)
            break;
        case G4:
            fgate.g_x = 1 + rand()%(max_height-4);    //gate4(rand,max)
            fgate.g_y = max_width-1;
            break;
        }

        switch ((enum LayerType)secondLayer)
        {
        case G1:
            sgate.g_y = 1 + rand()%(max_width-4);    //gate1(0,rand)
            break;
        case G2:
            sgate.g_x = 1 + rand()%(max_height-4);    //gate2(rand,0)
            break;
        case G3:
            sgate.g_x = max_height-1;
            sgate.g_y = 1 + rand()%(max_width-4);    //gate3(max,rand)
            break;
        case G4:
            sgate.g_x = 1 + rand()%(max_height-4);    //gate4(rand,max)
            sgate.g_y = max_width-1;
            break;
        }
        if (fgate.g_x != sgate.g_x || fgate.g_y != sgate.g_y) break;
    }

    /* Set color gate */
    mvwaddch(play,fgate.g_x,fgate.g_y,'X' | A_UNDERLINE | COLOR_PAIR(1));
    mvwaddch(play,sgate.g_x,sgate.g_y,'X' | A_UNDERLINE | COLOR_PAIR(1));

    wrefresh(play);
}
    /*
    밥 먹는 것은 여기서 처리를 하였는데, 독 먹는것도 move에서 어떻게든 처리를 해서 간결하게 해보려 했는데...
    쉽지 않네요 ;ㅁ; 
    가능 하신 능력자분이 계신다면 부탁드려요.
    
    */
void snake::move(){

    // 키를 입력 받습니다.
    // Rsnake에서 하나 없어질 때 마다 Tempsnake에 하나 씩 그리기
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

    // 벽에 부딪힌 것을 표현 하기 위해서 시도를 해봤는데, flag를 사용하는게 그나마 쉬운 것 같아서 사용했습니다.
    // flag == > 벽에 부딪혔니? --> flag가 1이면 맨 아래의 start() 함수에서 break를 통해 게임이 끝나게 됩니다.


    if(!get){
		mvwprintw(play,Rsnake[Rsnake.size()-1].y,Rsnake[Rsnake.size()-1].x," ");
        map[Rsnake[Rsnake.size()-1].y][Rsnake[Rsnake.size()-1].x] = 0;  // 지나간 자리는 map에서 0으로 초기화
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
    mvwprintw(play,Rsnake[0].y,Rsnake[0].x,"O");
    map[Rsnake[0].y][Rsnake[0].x]=3;
    
    
    wrefresh(play);

}

void snake::start(){
    make_gate();

    while(true){   
        if(collision()){
            wattron(play,COLOR_PAIR(1));
            mvwprintw(play,10,19,"G A M E O V E R");
            wrefresh(play);
            break;
        }
        move();
        
        if (flag==1){
            wattron(play, COLOR_PAIR(1));
            mvwprintw(play,10,19,"G A M E O V E R");
            wrefresh(play);
            break;
        }

        //flag initialize
        flag =0;

        //usleep 값에따라 지렁이 속도가 달라집니다. 원하시는 대로 설정 해주세요.
        usleep(current_speed);
        
        
    }

}
