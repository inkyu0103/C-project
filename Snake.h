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
#define MAX_LENGTH 10
#define INIT_SPEED 100000
struct snakeBody{
    int x,y;
    snakeBody(int col,int row);
    snakeBody();

};


class snake{
    std::vector<snakeBody> Rsnake;
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

    // snake's food
    snakeBody food; // o
    snakeBody poison; 
    char food_char;
    void generatefood();
    void generatepoison();
    bool collision();
    void move();
    

    public :
    snake();
    ~snake(); // Because we allocate 2nd array for making map
    void start();
    

};


#endif
