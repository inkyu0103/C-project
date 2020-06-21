# C++ project


게임을 만들기 위해 cpp 파일과 헤더를 나눠도 되고 현재의 main.cpp에 한꺼번에 다 몰아 넣어도 큰 무리는 없을 것 같습니다.

만약 여러 파일로 나누어서 진행하는게 편하실 것 같으면 다시 나누어서 올리겠습니다. 

-------

<ul>1단계

+ Ncurses Library 함수를 사용하여 2차원 배열로 된 Snake Map을 Game 화면으로 표시하는 프로그램을 완성한다. 
+ Map은 21X21을 최소 크기로 한다.
+ Complie : <code>g++ -g -o main main.cpp -lncursesw </code>
+ Mac Compile : <code> g++ -g -o main main.cpp Snake.cpp -lncurses </code>

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


### 현재 구현 된 것

-움직이는 것
-밥먹으면 길이가 늘어나는 것
-독약 먹으면 길이가 줄어드는 것

-밥(+)먹으면 10점 늘어나는 것
-독약(-) 먹으면 10점 감소하는 것

- 몸 길이가 2가 되면 Game over
- 점수가 0보다 작아지면 Game over
### (6.12)
- 보드 형식에 맞춰서 올라가는 것 구현(Gate는 구현 필요)
- 먹이를 먹으면 빨라지고, 독을 먹으면 느려짐
- 먹이 2번 먹으면 더 이상 먹이가 안 나오는 버그가 있음(제 생각에는 먹이 먹었는지 검사하는 부분을 collision밖으로 빼야할 것 같아요)
- mission
- Stage 1: +(3) -(1) g(0)
- Stage 2: +(5) -(2) g(1)
- Stage 3: +(7) -(3) g(1)
- Stage 4: +(9) -(4) g(2)

### (6.13)
- Gate 구현 완료
- 반대 Gate로 나오는 부분 구현 필요

### (6.21) 
- Gate 반대편으로 까지 나오게 하기 구현
- 미션 조건을 충족하면 다음 스테이지로 넘어가는 것 구현
- 미션 조건을 일부 완성하면 Mission 판에 (v) 체크 되게 하는 기능 구현


### 구현 해야 하는 것
#### RULE 1(완료)
-food /poison 시간에 따른 위치 변경 (완료)

### RULE 2 (완료)

### RULE 3 (완료)

### RULE 4 (;ㅁ;)
-여기는 사실 gate가 가장자리가 아닌 곳에 생성될때를 전제로 하고 있는데... 남은 시간동안 할 수 있을까요...? 할 수 있으면 되는대로 해볼게요

### RULE 5 (완료)
- Gate의 출현 방법은... 그냥 맵이 생성되는 동시에 gate가 생성되는걸로 해야할 것 같네요.

### RULE 6 (미완성) 
- 몸의 초대길이 계산 (완료)
- 게임중 획득한 food 수 (완료)
- 게임중 획득한 poison 수 (완료)
- 게임중 Gate 사용수 (완료)
- 게임시간 (Seconds로 계산---> 미완성)




### 맵 생성 시 참고할 점

- 예를 들어 4단계의 맵을 수정한다고 가정해볼게요



      else if (level == 4 ){  --> 3단계를 수정하시고 싶으시면 level == 3 인 곳을 수정하시면 됩니다.
        mvprintw(1,20,"STAGE 4");

        mission_food =9;
        mission_poison =4;
        mission_gate = 2;

        map = new int*[y];   // row 개만큼 할당 받고, 각 row마다 col개만큼 다시 할당받는다.
        for(int i=0;i<y;i++){
            map[i]=new int[x];
        }

        이 부분을 건드리시면 됩니다. (아래 for문에 걸쳐있는 row와 col의 조건을 다르게 하여 맵을 만들어주시면 됩니다.)
        1. 현재 가로 46 (0~45) , 세로 23 (0~22) 의 길이를 가지는 맵을 가지고 수정을 해야합니다.
        참고하셔야 할 점은 뱀의 초기 생성 위치가 (24,11) ~ (26,11) 입니다. 만약에 내가 맵을 만드는데 뱀 초기위치가 거슬린다 하시면
        
        for(int i=0;i<3;i++){
        Rsnake.push_back(snakeBody(24+i,11));  //24 가 x좌표고 ,11이 y좌표 
        }
        
        이 부분을 각 맵을 생성하는 곳에 따로 좌표를 설정하셔서 넣으면 됩니다.
        지금은 레벨별로 맵을 생성하는 바깥부분에 있어서 모든 레벨에서 동일한 좌표에서 뱀이 생성됩니다.
        
        이 과정이 번거로우시면... 뱀 초기위치를 피해서 맵을 만드시면 됩니다.
        
        2.
        map[][] 배열에 값을 집어넣기 위해서는 'map[y좌표][x좌표] = 값' 의 형태로 넣어주셔야 합니다.
        
        1단계와 달리 2,3,4 단계는 맵 가운데에 무언가 들어갈 가능성이 있기 때문에 map[][]에 1(wall)이나 2(immune wall)의 값을 넣으신 후
        화면에 직접 업데이트를 해주셔야 합니다. 
        
        mvwprintw(play,y좌표,x좌표,원하는 글자);
        wrefresh(play);
        
        의 방식으로 업데이트 해주시면 됩니다.
         
       
        for(int row = 0;row< y;row++){
            for(int col = 0; col < x; col++){
                // Wall
                if ((row==0 && col==0) || (row== 0 && col == x-1) || (row == y-1 && col == 0)|| (row == y-1 && col == x-1)){
                    map[row][col]=2;

                }
                // immune Wall
                else if(row == 0 || col == 0  || col == x-1 || row ==y-1 ){
                    map[row][col] = 1;
                }
                // empty space
                else{
                    map[row][col] = 0;

                }
            }
        }
    }






