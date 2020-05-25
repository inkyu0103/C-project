# C++ project


게임을 만들기 위해 cpp 파일과 헤더를 나눠도 되고 현재의 main.cpp에 한꺼번에 다 몰아 넣어도 큰 무리는 없을 것 같습니다.

만약 여러 파일로 나누어서 진행하는게 편하실 것 같으면 다시 나누어서 올리겠습니다. 

-------

<ul>1단계

+ Ncurses Library 함수를 사용하여 2차원 배열로 된 Snake Map을 Game 화면으로 표시하는 프로그램을 완성한다. 
+ Map은 21X21을 최소 크기로 한다.
+ Complie : <code>g++ -g -o main main.cpp -lncursesw </code>

+ 구현 방식
  +  2차원 배열을 할당받아 맵을 만들었습니다. (현재 맵의 크기는 가로 46, 세로 23입니다. 가로 2칸이 세로 1칸과 크기가 동일하여 정사각형을 만들고 싶어서 일단 이렇게 설정은 했습니다.)
  
  +  ~~~ 
     int** map;
     map = new int*[y];
     for(int i=0;i<y;i++){map[i]=new int[x]};}
     
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
     ~~~
     + map[row][col] == 1 --> Immune Wall
     + map[row][col] == 2 --> Wall (Gate 생성 x)
     + map[row][col] == 3 --> snake_head (추후)
     + map[row][col] == 4 --> snake_body (추후)
</ul>




