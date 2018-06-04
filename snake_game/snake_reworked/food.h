#ifndef FOOD_H_
#define FOOD_H_
#include "pos.h"
#include <vector>
#include<stdio.h>
#include<stdlib.h>

class Food{
public:
	Position pos;
	
	//updates food position randomly so as not to hit head or body
	void update(std::vector<Position> &body,int hx,int hy);
};

#endif