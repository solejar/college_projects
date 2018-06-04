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


//need to implement end funtion()
int Game::end()                  //exit game function
{
    system("stty echo icanon");     //restart cache
	//TODO
	//need to make cursor goto the bottom
	//need to show cursor
	
	
	
    exit(0);                        //exit
}

int Game::getKey()                  //key control function
{
    //TODO
	//need to implement this function
	//which will take a infinite loop to 
	//set direction of snake head
	

}


//function use to draw a box
void Game::drawBox()                     //draw the outer range
{
    pen.clr_scrn();
    pen.draw_box(1,20,ROW,COL,44,34,'#');
}
 
void Game::drawSnake(void)                   // draw snake
{
    //TODO
	//need to draw the snake out
	//draw head
	//use loop to draw body
}

void Game::snakeMove(void)                   //move snake
{
    
	//TODO
	//need to check if the head space is valid 
	//if it is valid check if the space has food
	//if it has food-->update food && update body
	//make movement
	//update head position
	//use fkey(fault key) to check the wrong direction
}

void Game::start(){
    int quit = 0;
    while(!quit)
    {
        system("stty -echo -icanon");   //cancel cache；
        pen.hide_cur();                     
        pen.clr_scrn();                     
        drawBox();                     
 
        //TODO
		//need to draw a welcome page
		//need to add more feature in the switch below
		
		
        fflush(stdout); //flush the buffer
        int back = 0;
        while(!back)
        {
            int ret;
            char key = '0';
            int i;
            key = get_key();            //get key
            switch(key)
            {
                case ???:                // start game,??? is the key you use to start game
					gameStart();
					std::thread f1([&](){
						handler();
					});
					std::thread f2([&](){
						getKey();
					});
					f1.join();
					f2.join(); 
 
                    back = 1;           // note for end
                    break;
            }   
 
        }
    }
    end();                     // end of game
}


//handler is use to draw food and update snake position
void Game::handler(){
		
	//TODO
	//use a infinite loop
	//draw the game box
	//draw th food
	//move the snake
	//flush the cache
	//use usleep(speed) to control speed
}

void Game::gameStart(){
    snake.head.pos.x = 10;                  //init the head position
    snake.head.pos.y = 20; 
	snake.body.add(10,19);			//init the body position
	snake.body.add(10,18); 
	snake.body.add(10,17);          
    fkey = 'r';                   //direction
    snake.head.direction = RIGHT;                //head direction
    speed=401;
    food.update(snake.body.body_,snake.head.pos.x,snake.head.pos.y);                      //init food position
}



