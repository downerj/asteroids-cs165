/*****************************************************************************
 * File: Driver.cpp
 * Author: Br. Burton, James D. Downer
 *
 * Description: This file contains the main function that starts the game and
 *  the callback function that specifies what methods of the game class are
 *  called each time through the game loop.
 *****************************************************************************/

#include <ctime>   // time()
#include <cstdlib> // rand(), srand()
using namespace std;

#include "game.hpp"
#include "uiInteract.hpp"

/*****************************************************************************
 * DRIVER
 *****************************************************************************/

/*****************************************************************************
 * All the interesting work happens here, when  I get called back from OpenGL
 * to draw a frame. When I am finished drawing, then the graphics engine will
 * wait until the proper amount of time has passed and put the drawing on the
 * screen.
 *****************************************************************************/
void callBack(const Interface *pUI, void *p)
{
   Game * pGame = (Game *)p;
   
   pGame->advance();
   pGame->handleInput(*pUI);
   pGame->draw(*pUI);
}

/*****************************************************************************
 * Main is pretty sparse. Just initialize the game and call the display engine.
 * That is all!
 *****************************************************************************/
int main(int argc, char ** argv)
{
   Point topLeft(-200, 200);
   Point bottomRight(200, -200);
   
	srand(time(NULL));
	
   Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
	ui.setFramesPerSecond(40);
   Game game(topLeft, bottomRight);
   ui.run(callBack, &game);
   
   return 0;
}
