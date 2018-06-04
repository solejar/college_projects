#include "game.h"
 
//get_key will return the key user typed
char Game::get_key() 
{
    int n;
    char buf[3];
    n = read(0,buf,sizeof(buf));
    if(3 == n && buf[0] == 27 && buf[1] == 91)
    {
        return buf[2];
    }
    else if(1 == n)
    {
        return buf[0];
    }
    return 0;
}


//ends game
int Game::end()                  //exit game function
{
    system("stty echo icanon");     //restart cache
	
	//resets cursor position, shows cursor
	pen.goto_xy(23,0);
	pen.show_cur();	
	
    exit(0);                        //exit
}

int Game::getKey()              //key control function
{
	while(true){
		//gets key input from user
		char key='0';
		key =get_key();

		//key input drives switch case structure
		switch(key){
			//if user presses up, snake goes up
			case UP:
				snake.head.direction = UP;
				break;
			//if user presses down, snake goes down
			case DOWN:
				snake.head.direction = DOWN;
				break;
			//if user presses left, snake goes left
			case LEFT:
				snake.head.direction = LEFT;
				break;
			//if user presses right, snake goes right
			case RIGHT:
				snake.head.direction = RIGHT;
				break;
		}
	}
	return 0;
}

//function draws the game box
void Game::drawBox()                     
{
    pen.clr_scrn();
    pen.draw_box(1,20,ROW,COL,44,34,'#');
}

//draws snake 
void Game::drawSnake(void)                  
{
	//draws body elements using a loop
    for(int i = 0;i<snake.body.count();i++){
    	  pen.draw_rect(snake.body.body_[i].x,snake.body.body_[i].y,1,1,2,3,'@');
    }
    //draws the head
    pen.draw_rect(snake.head.pos.x,snake.head.pos.y,1,1,3,3,'D');
}

//moves snake
void Game::snakeMove(void)                 
{
	//if head collides with wall, end
	if (snake.head.pos.x==2||snake.head.pos.x==(ROW+1)||snake.head.pos.y==20||snake.head.pos.y==(COL+20)){
		end();
	}

	//if head collides with body, end
	//iterates through all body elements to check if there is collision
	for(int i=0;i<snake.body.count();i++){
		if((snake.head.pos.x==snake.body.body_[i].x)&&(snake.head.pos.y==snake.body.body_[i].y)){
			end();
		}
	}
	
	//if head collides with food, do this
	if((snake.head.pos.x==food.pos.x)&&(snake.head.pos.y==food.pos.y)){
		//update food position
		food.update(snake.body.body_,snake.head.pos.x,snake.head.pos.y);
		//add a piece to the body (position is irrelevant as will be changed by snakeMove)
		snake.body.add(0,0);
		//make the game a little harder
		makeHarder();
	}

	//moves the snake body
	snake.body.move(snake.head.pos.x,snake.head.pos.y);

	//updates head position
	switch(snake.head.direction){
		//use fkey(fault key) to check the wrong direction
		//if not going in mutually exclusive direction, change head coordinates and fault key updates
		case UP:
			if(fkey!='d'){
				snake.head.pos.x-=1;
				fkey='u';
			}else{
				snake.head.pos.x+=1;
			}
			break;
		case DOWN:
			if(fkey!='u'){
				snake.head.pos.x+=1;
				fkey = 'd';
			}else{
				snake.head.pos.x-=1;
			}
			break;
		case LEFT:
			if(fkey!='r'){
				snake.head.pos.y-=1;
				fkey= 'l';
			}else{
				snake.head.pos.y+=1;
			}
			break;
		case RIGHT:
			if(fkey!='l'){
				snake.head.pos.y+=1;
				fkey= 'r';
			}else{
				snake.head.pos.y-=1;
			}
			break;
	}
}

//starts the game when space is pressed
void Game::start(){
    int quit = 0;
    while(!quit)
    {
        system("stty -echo -icanon");   //cancel cache；
        //hides cursor, clears screen
        pen.hide_cur();                     
        pen.clr_scrn();              
        //draws game box for main menu       
        drawBox();                     
 		
 		//prints the main menu
		mainMenu();	
		
		//flushes the buffer
        fflush(stdout); 
        int back = 0;
        while(!back)
        {
            int ret;
            //key holds user input
            char key = '0';
            int i;
            //gets key from user
            key = get_key();            
            switch(key)
            {
            	//one and two display menus, space starts game
            	case ONE:
            		//displays rules and flushes screen to user
            		drawBox();
            		displayRules();
            		fflush(stdout);
            		break;
            	case TWO:
            		//displays menu and flushes screen to user
            		drawBox();
            		mainMenu();
            		fflush(stdout);
            		break;
                case SPACE:
                	//starts game when you press space         

                	//initializes game variables
					gameStart();

					//this thread handles the game itself
					std::thread f1([&](){
						handler();
					});
					//this thread constantly seeks user input to change snake direction
					std::thread f2([&](){
						getKey();
					});
					//this thread constantly ticks score up 10 points every second
					std::thread f3([&](){
						while(1<2){
							scoreTotal+=10;
							usleep(1700000);
						}		
					});
					f1.join();
					f2.join(); 
					f3.join();
 
                    back = 1;           // note for end
                    break;
            }   
 
        }
    }
    end();                     // end of game
}


//handler draws food and updates snake position
void Game::handler(){		
	while(true){
	
	//draws game box
	drawBox();
	
	//draw food
	pen.draw_rect(food.pos.x,food.pos.y,1,1,6,6,'X');

	//move the snake
	snakeMove();
	//draw snake
	drawSnake();

	//print score
	printScore();

	//flush the cache
	fflush(stdout);
	//use usleep(speed) to control speed
	usleep(speed);
	}
}

//prints rules on main page
void Game::displayRules(){
	pen.goto_xy(4,24);
	pen.putstr(6,6,"Rules:");
	pen.goto_xy(7,23);
	pen.putstr(6,6,"You are a snake on a yummy journey");
	pen.goto_xy(8,25);
	pen.putstr(6,6,"to eat all the X's!");
	pen.goto_xy(10,23);
	pen.putstr(6,6,"As you eat the food, you will grow,");
	pen.goto_xy(11,23);
	pen.putstr(6,6,"increasing in both size and speed.");
	pen.goto_xy(13,23);
	pen.putstr(6,6,"Don't hit the wall or eat yourself!");
	pen.goto_xy(16,23);
	pen.putstr(6,6,"Press 'Space' to play");
	pen.goto_xy(17,26);
	pen.putstr(6,6,"or '2' to go back");
}

//prints main menu
void Game::mainMenu(){
	pen.goto_xy(8,27);
	pen.putstr(6,6,"Welcome to the Snake Game!");
	pen.goto_xy(11,27);
	pen.putstr(6,6,"Press 'Space' to Continue");
	pen.goto_xy(12,29);
	pen.putstr(6,6,"or press '1' for rules");
}

//prints score
void Game::printScore(){
	pen.goto_xy(2,62);
	//uses ostream to append score to string
	std::ostringstream oss;
	oss << scoreTotal;
	std::string score_out = "Score: ";
	score_out += oss.str();

	//then prints string
	pen.putstr(6,6,score_out);
}

//makes game harder
void Game::makeHarder(){
	//speed threshold, faster than this will break game
	if(speed>63000){
		//speed up by factor equal to hard_factor
		speed=speedOriginal/hard_factor;
	}		
	//score increase goes up as difficulty goes up
	scoreTotal += scoreIncrease*hard_factor;
	//symbolic "difficulty" gets bigger everytime food eaten
	hard_factor = 1.12*hard_factor;
}

//initializeds variables
void Game::gameStart(){
	//initializes the head position
    snake.head.pos.x = 13;                 
    snake.head.pos.y = 24; 

    //init the body position
	snake.body.add(12,24);			
	snake.body.add(11,24); 
	snake.body.add(10,24);

	//init the direction          
    fkey = 'd';                   
    snake.head.direction = DOWN;    

    //init the speed           
    speed=250000;
    speedOriginal = speed;

    //init score and difficulty
    scoreTotal = 0;
    hard_factor = 1;
    scoreIncrease = 100;

    //init food position
    food.update(snake.body.body_,snake.head.pos.x,snake.head.pos.y);                      
}



