/*********************************************************************
 * File: game.hpp
 * Author: James D. Downer
 * Description: Defines the game class for Asteroids
 *********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "uiInteract.hpp"
#include "point.hpp"
#include "stars.hpp"
#include "bullet.hpp"
#include "ship.hpp"

#define CLOSE_ENOUGH 15
#define OFF_SCREEN_BORDER_AMOUNT 15

/*****************************************************************************
 * GAME
 * This emulates a game class that contains the data and methods to run this
 * specific Asteroids game.
 *****************************************************************************/

class Game
{
	
public:
	// Constructor
	Game(const Point & topLeft, const Point & bottomRight);
	
	// Destructor
	~Game();
	
	// Functions for OpenGL callback (main subroutines of program)
	void advance();
	void handleInput(const Interface & interface);
	void draw(const Interface & interface);
	
private:
	// The coordinates of the screen
   Point topLeft;
   Point bottomRight;
	Point minimum;	
	Point maximum;
   int   score;
	int   lives;
	float hitRatio;
	int   shots;
	bool  canFireShockwave;
   
	// The moving objects
	std::vector<Bullet *>       bullets;
	std::vector<Asteroid *>     asteroids;
	std::vector<ShootingStar *> shootingStars;
	std::vector<NormalStar *>   normalStars;
	
	Ship * pShip;
	Shockwave * pShockwave;
	
   /*************************************************
    * Private methods to help with the game logic.
    *************************************************/
	float getClosestDistance(Moveable & obj1, Moveable & obj2) const;
   void  advanceBullets();
   void  advanceShip();
	void  advanceAsteroids();
	LargeAsteroid  * createLargeAsteroid();
	MediumAsteroid * createMediumAsteroid(Asteroid * aster,
													  float ddx, float ddy);
	SmallAsteroid  * createSmallAsteroid(Asteroid * aster,
													 float ddx, float ddy);
	
	void  wrapObject(Moveable * obj, const Point & min, const Point & max);  
   void  handleCollisions();
   void  cleanUpZombies();
	void  emptyVectors();
};

#endif /* GAME_HPP */
