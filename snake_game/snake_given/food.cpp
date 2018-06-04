#include "food.h"

//need to update the random food position
//need to be implemented
void Food::update(std::vector<Position> &body,int hx,int hy){
    int i;
    int flag = 0;
    while(1)
    {
        pos.x = (rand() % (ROW - 2)) + 2;
        pos.y = (rand() % (COL - 2)) + 2;
 
        //TODO
		//need to check if the food position is valid
 
        if(flag)
        {
            break;
        }
        continue;
    }
}