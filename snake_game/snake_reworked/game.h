#ifndef GAME_H_
#define GAME_H_
#include "food.h"
#include "snake.h"
#include "pen.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <sstream>
 
#define SPACE    32
#define ESC      27
#define UP       65
#define DOWN     66
#define RIGHT    67
#define LEFT     68
//define more macros for my menu
#define ONE      49
#define TWO      50



class Game{
public:
	//makes the game execute
	void start();
	
private:
	//initializes variables needed to start playing
	void gameStart();
	//handles the while loop that makes the game run
	void handler();
	//returns whatever keys the user presses as a char
	char get_key();
	//restores the cursor and terminates the game
	int end();
	//infinite while loop which sets direction of snake head to direction of user key press
	int getKey();
	//draws the game box
	void drawBox();
	//draws snake every iteration of handler function
	void drawSnake();
	//moves snake every iteration of handler function
	void snakeMove();
	//updates position of the food after it gets eaten
	void updateFood();
	//prints current score in top right corner
	void printScore();
	//increases speed, making game "harder"
	void makeHarder();
	//prints rules on main menu
	void displayRules();
	//prints main menu
	void mainMenu();

	//instantiation of necessary objects
	Pen pen;
	Food food;
	Snake snake;

    //char to hold last key input of user
	char fkey;
	//int that controls how long handler loop sleeps before repeating
    int speed;
    //speed before any increase in difficulty
    int speedOriginal;
    //total score
    int scoreTotal;
    //how much score goes up by everytime you eat food
    int scoreIncrease;
    //double that holds current 'difficulty factor', used to determine score increase and speed
    double hard_factor;
};


#endif