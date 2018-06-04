#include "body.h"

//this function moves all body locations one by one
void Body::move(int x1,int y1){
	
	//for loop iterates through all body elements
	for(int i=(count()-1);i>0;i--){
		//sets location of each part to the location of where the part ahead used to be
		body_[i].x = body_[i-1].x;
		body_[i].y = body_[i-1].y;
	}
		//sets location of frontmost part to old location of head	
		body_[0].x = x1;
		body_[0].y = y1;
}
