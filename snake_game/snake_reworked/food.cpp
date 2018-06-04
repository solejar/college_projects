#include "food.h"

//randomly changes food position, won't hit body or head
void Food::update(std::vector<Position> &body,int hx,int hy){
    int i;
    int flag = 1;
    //use flag as break condition for while loop below
    //needs to remain 1 to exit loop
    while(1)
    {
        //pos is random number within row,col bounds
        pos.x = (rand() % (ROW - 2)) + 2;
        pos.y = (rand() % (COL - 2)) + 22;
 
		//checks if food position is valid
        if(((pos.x==hx)&&(pos.y==hy))){
            flag = 0;
            //if food generated at head, no good, sets flag to 0
        }
        //checks through all elements of body
        for(int i=0;i<body.size();i++){
            if(pos.x==body[i].x&&pos.y==body[i].y){
                flag = 0;
                //if food generated at body, no good, sets flag to 0
            }
            if(!flag){
                //first invalid body element will break loop
                //stopping loop from unnecessarily checking other body elements too
                break;
            }
        }
        //if flag still 1 by now, position is good!
        if(flag){
            break;
        }
    }
}