  
#include<iostream> //0
#include<ncurses.h>//0
#include<vector>//0
#include<cstdlib>//0
#include<clocale>
#include <unistd.h>//0
#include<string>
#include<time.h>

#ifndef SNAKE_H
#define SNAKE_H
#define INIT_LENGTH 3
#define MAX_LENGTH 15
#define INIT_SPEED 100000
using namespace std;
struct snakeBody{
    int x,y;
    snakeBody(int col,int row);
    snakeBody();

};
struct gatePos{
    int g_x,g_y;
    gatePos(int g_col,int g_row);
    gatePos();
};
enum LayerType {
    G1 = 0,
    G2,
    G3,
    G4
};

class snake{
    snake(int level = 0);
    
    vector<snakeBody> Rsnake;
    vector<snakeBody> Tempsnake;
    WINDOW * score;
    WINDOW * mission;
    WINDOW * play;

    int x,y; // play window 의 max_width & max_height
    int flag;
    int del;
    int point; //o
    int **map ; // o
    int max_width; // o 
    int max_height;// o 
    int body_length; // 
    int food_cnt;   //먹이 먹은 갯수
    int poison_cnt; //독 먹은 갯수
    int gate_cnt;   //gate 사용횟수
    int speed_interval;
    int current_speed;
    char direction; // o 
    bool get;
    bool poi;
    bool enter_gate;
    gatePos fgate;
    gatePos sgate;
    int fline;
    int sline;
    time_t start_time;
    time_t end_time;
    double result;
    // snake's food
    snakeBody food; // o
    snakeBody poison; 
    gatePos gate;
    char food_char;
    void generatefood();
    void generatepoison();
    void make_gate();
    bool collision();
    void move();
    

    public :
    snake();
    ~snake(); // Because we allocate 2nd array for making map
    void start();
    

};


#endif
