#include<iostream>
#include<ncurses.h>
#include<vector>
#include<cstdlib>
#include<clocale>

#ifndef SNAKE_H
#define SNAKE_H

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


    int socre; //o
    int **map ; // o
    int max_width; // o 
    int max_height;// o 
    int body_length; // 
    char direction; // o 
    bool get;

    // snake's food
    snakeBody food; // o
    char food_char;
    void generatefood();
    bool collision();
    void move();
    

    public :
    snake();
    ~snake(); // Because we allocate 2nd array for making map
    void start();
    

};







#endif