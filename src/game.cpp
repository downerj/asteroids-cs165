/*********************************************************************
 * File: game.cpp
 * Author: James D. Downer
 * Description: Contains the implementaiton of the game class
 *  methods.
 *********************************************************************/

#include <cmath>
using namespace std;

#include "game.hpp"
#include "point.hpp"
#include "velocity.hpp"
#include "stars.hpp"
#include "ship.hpp"
#include "bullet.hpp"
#include "color.hpp"
#include "uiInteract.hpp"
#include "uiDraw.hpp"
#include "moveable.hpp"

// These are needed for the getClosestDistance function
#include <limits>
#include <algorithm>

/*****************************************************************************
 * GAME CLASS
 *****************************************************************************/

#define NUM_ASTEROIDS       5
#define NUM_SHOOTING_STARS 10
#define NUM_NORMAL_STARS   50

/*****************************************************************************
 * Default Constructor
 * Initialize the game.
 *		Set the score to 0.
 *    Set the lives to 5.
 *    Set the hit-miss ratio and helper data to 0.
 *    Initially disable shockwave (Z-button).
 *    Create 5 large asteroids.
 *    Create shooting stars and background stars.
 *****************************************************************************/
Game :: Game(const Point & tl, const Point & br)
: topLeft(tl), bottomRight(br)
{
   // Set up the initial conditions of the game
   score = 0;
	lives = 5;
	hitRatio = 0.0;
	shots = 0;
	canFireShockwave = false;
	
   // Set ship pointer to initial null
	pShip = new Ship;
	pShockwave = NULL;
	
	// Extract data to create Point extrema
	minimum.setX(topLeft.getX()     - OFF_SCREEN_BORDER_AMOUNT);
	minimum.setY(bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT);
	maximum.setX(bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT);
	maximum.setY(topLeft.getY()     + OFF_SCREEN_BORDER_AMOUNT);
	
	// Create large asteroids to start
	for (int i = 0; i < NUM_ASTEROIDS; i++)
		asteroids.push_back(createLargeAsteroid());
	 
	// Create shooting stars
	float magnitude1 = 2.0;
	float angle      = random(0.0, 360.0);
	for (int i = 0; i < NUM_SHOOTING_STARS; i++)
	{
		float x = random(topLeft.getX(), bottomRight.getX());
		float y = random(bottomRight.getY(), topLeft.getY());
		
		ShootingStar * pStar = new ShootingStar;
		pStar->setMagnitude(magnitude1);
		pStar->setAngle(angle);
		pStar->setX(x);
		pStar->setY(y);
		shootingStars.push_back(pStar);
	}
	
	// Create normal stars (background)
	float magnitude2 = 0.1;
	for (int i = 0; i < NUM_NORMAL_STARS; i++)
	{
		float x = random(topLeft.getX(), bottomRight.getX());
		float y = random(bottomRight.getY(), topLeft.getY());
		
		NormalStar * pStar = new NormalStar;
		pStar->setMagnitude(magnitude2);
		pStar->setAngle(angle);
		pStar->setX(x);
		pStar->setY(y);
		normalStars.push_back(pStar);
	}
}

/*****************************************************************************
 * Destructor
 *****************************************************************************/
Game :: ~Game()
{
	if (pShip)
		delete pShip;
	
	if (pShockwave)
		delete pShockwave;
	
	emptyVectors();
}

/*****************************************************************************
 * ADVANCE
 * Update the data in all of the flying objects (including movement, collision,
 * and garbage collection).
 *****************************************************************************/
void Game :: advance()
{
   advanceBullets();
	advanceAsteroids();
   advanceShip();
	
   handleCollisions();
   cleanUpZombies();
}

#define MAX_SHOCKWAVE_RADIUS 500
/*****************************************************************************
 * HANDLE INPUT
 * Get input from the keyboard.
 *		LEFT		Turn ship counter-clockwise.
 *    RIGHT		Turn ship clockwise.
 *    UP			Accelerate the ship in the direction it is pointed.
 *    DOWN		Slow the ship down (or stop it, if slow enough).
 *		SPACE		Shoot single bullets.
 *    X        Fire string of bullets.
 *    Z        (If enabled) fire a shockwave.
 *
 * INPUT:	interface		The OpenGL UI object.
 *****************************************************************************/
void Game :: handleInput(const Interface & interface)
{
	if (pShip)
	{
		// Set bullet's point at tip of the ship nose
		Point p = pShip->getPoint();
		Velocity v(5.0, pShip->getRotation());
		p += v;
		
		if (interface.isLeft())
			pShip->rotateCounterClockwise();
		if (interface.isRight())
			pShip->rotateClockwise();
		if (interface.isUp())
			pShip->thrustUp();
		if (interface.isDown())
			pShip->thrustDown();
		
		if (!(interface.isLeft() || interface.isRight() ||
				interface.isUp()   || interface.isDown()))
			pShip->thrustOff();
		
		if (interface.isSpace())
		{
			Bullet * pBullet = new Bullet;
			
			pBullet->fire(p, pShip->getRotation(), 5);
			pBullet->addDx(pShip->getVelocity().getDx());
			pBullet->addDy(pShip->getVelocity().getDy());
			
			bullets.push_back(pBullet);
			shots++;
			cout << "# Bullets: " << bullets.size() << endl;
		}
		
		if (interface.isX())
		{
			Bullet * pBullet = new Bullet;
			
			pBullet->fire(p, pShip->getRotation(), 5);
			pBullet->addDx(pShip->getVelocity().getDx());
			pBullet->addDy(pShip->getVelocity().getDy());
			
			bullets.push_back(pBullet);
			shots++;
		}
		
		if (interface.isZ() && canFireShockwave)
		{
			if (!pShockwave)
			{
				pShockwave = new Shockwave;
				pShockwave->setMaxRadius(MAX_SHOCKWAVE_RADIUS);
				pShockwave->fire(pShip->getPoint());
			}
		}
	}
}

/*****************************************************************************
 * DRAW
 * Draw all of the live flying objects and put data on the screen.
 *
 * INPUT:	interface		The OpenGL UL object.
 *****************************************************************************/
void Game :: draw(const Interface & interface)
{	
	vector<NormalStar *> :: iterator it5;
	for (it5 = normalStars.begin(); it5 != normalStars.end(); ++it5)
		if (*it5 && (*it5)->isAlive())
			(*it5)->draw();
	
	vector<ShootingStar *> :: iterator it4;
	for (it4 = shootingStars.begin(); it4 != shootingStars.end(); ++it4)
		if (*it4 && (*it4)->isAlive())
			(*it4)->draw();
	
	vector<Asteroid *> :: iterator itA;
	for (itA = asteroids.begin(); itA != asteroids.end(); ++itA)
		if (*itA && (*itA)->isAlive())
			(*itA)->draw();
	 
	vector<Bullet *> :: iterator it0;
	for (it0 = bullets.begin(); it0 != bullets.end(); ++it0)
		if (*it0 && (*it0)->isAlive())
			(*it0)->draw();
	
	if (pShockwave && pShockwave->isAlive())
		pShockwave->draw();
	 	
	if (pShip)
	{
		if (pShip->isAlive())
			pShip->draw();
		
		/** Put data on the screen **/
		Color color0(1.0, 0.0, 1.0); // Magenta
		Color color1(0.7, 0.7, 0.7); // Grey
		Color color2(1.0, 1.0, 1.0); // White
		Color color3(0.0, 0.5, 1.0); // Blue-cyan
		Color color4(0.0, 1.0, 1.0); // Cyan
		Color color5(0.0, 1.0, 0.0); // Green
		Color color6(1.0, 0.0, 0.5); // Pink
		Color color7(1.0, 1.0, 0.0); // Yellow
		
		int posX = topLeft.getX() + 5;
		int posY = topLeft.getY() - 5;
		
		// Framerate (FPS)
		Point fpsTextLoc;
		fpsTextLoc.setX(posX);
		fpsTextLoc.setY(posY);
		drawNumber(fpsTextLoc, interface.getFramesPerSecond(), color0);
		
		// Current Ship Time Alive
		Point framesTextLoc;
		framesTextLoc.setX(posX);
		framesTextLoc.setY(posY -= 15);
		drawNumber(framesTextLoc, pShip->getFramesAlive() / 10, color6);
		
		// Ship Position X
		Point xTextLoc;
		xTextLoc.setX(posX);
		xTextLoc.setY(posY -= 15);
		drawNumber(xTextLoc, pShip->getPoint().getX(), color3);
		
		// Ship Position Y
		Point yTextLoc;
		yTextLoc.setX(posX);
		yTextLoc.setY(posY -= 15);
		drawNumber(yTextLoc, pShip->getPoint().getY(), color3);
		
		// Ship Velocity Angle
		Point angleTextLoc;
		angleTextLoc.setX(posX);
		angleTextLoc.setY(posY -= 15);
		drawNumber(angleTextLoc, (int)pShip->getVelocity().getAngle() % 360,
					  color4);
		
		// Ship Velocity Magnitude (x100)
		Point magTextLoc;
		magTextLoc.setX(posX);
		magTextLoc.setY(posY -= 15);
		drawNumber(magTextLoc, pShip->getVelocity().getMagnitude() * 100.0,
					  color4);
		
		// Ship Velocity Dx (x100)
		Point dxTextLoc;
		dxTextLoc.setX(posX);
		dxTextLoc.setY(posY -= 15);
		drawNumber(dxTextLoc, pShip->getVelocity().getDx() * 100.0, color1);
		
		// Ship Velocity Dy (x100)
		Point dyTextLoc;
		dyTextLoc.setX(posX);
		dyTextLoc.setY(posY -= 15);
		drawNumber(dyTextLoc, pShip->getVelocity().getDy() * 100.0, color1);
		
		// Score
		Point scoreTextLoc;
		scoreTextLoc.setX(posX);
		scoreTextLoc.setY(posY -= 15);
		drawNumber(scoreTextLoc, score, color5);
		
		// Hit-miss ratio
		Point hitMissTextLoc;
		hitMissTextLoc.setX(posX);
		hitMissTextLoc.setY(posY -= 15);
		drawNumber(hitMissTextLoc, hitRatio * 100, color7);
		
		// Number of lives (ship symbol x lives)
		Point livesSymbolLoc;
		int livesToDraw = (lives <= 20) ? lives : 20;
		for (int i = 0; i < livesToDraw; i++)
		{
			livesSymbolLoc.setX(maximum.getX() - 30 - i * 15);
			livesSymbolLoc.setY(maximum.getY() - 30);
			drawShip(livesSymbolLoc, 0.0, color2, 0);
		}
	}
}

/*****************************************************************************
 * GET CLOSEST DISTANCE
 * This functions finds the closest distance between two objects before and
 * after their velocity vectors are applied to see if they will cross paths.
 * This is used for collision detection to ensure that objects don't
 * "jump over" each other.
 *
 * INPUT:	obj1		The first object (by reference)
 *				obj2		The second object (by reference)
 *****************************************************************************/
float Game :: getClosestDistance(Moveable & obj1,
											Moveable & obj2) const
{
   // Find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()),
						  abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // When dx and dy are 0.0: go through the loop once
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() +
						 (obj1.getVelocity().getDx() * i / dMax),
						 obj1.getPoint().getY() +
						 (obj1.getVelocity().getDy() * i / dMax));
		
      Point point2(obj2.getPoint().getX() +
						 (obj2.getVelocity().getDx() * i / dMax),
						 obj2.getPoint().getY() +
						 (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

#define BULLET_LIFE        40
#define SCORE_TO_SHOCKWAVE 20
/*****************************************************************************
 * ADVANCE BULLETS
 * Update data for the bullets and shockwave.
 *****************************************************************************/
void Game :: advanceBullets()
{
	vector<Bullet *> :: iterator it0;
	for (it0 = bullets.begin(); it0 != bullets.end(); ++it0)
	{
		if ((*it0) && (*it0)->isAlive() &&
			 (*it0)->getFramesAlive() <= BULLET_LIFE)
		{
			(*it0)->advance();
			wrapObject(*it0, minimum, maximum);
		}
		else if (*it0)
		{
			(*it0)->kill();
			hitRatio = (float)score / (float)shots;
		}
	}	
	
	if ((score > 0) &&
		 ((score % SCORE_TO_SHOCKWAVE) == 0) &&
		 !canFireShockwave)
		canFireShockwave = true;
	
	if (pShockwave && pShockwave->isAlive() &&
		 pShockwave->getRadius() <= pShockwave->getMaxRadius())
		pShockwave->advance();
	else if (pShockwave)
	{
		pShockwave->kill();
		hitRatio = (float)score / (float)shots;
		canFireShockwave = false;
	}
}

/*****************************************************************************
 * ADVANCE SHIP
 * Update the ship's data and wrap its position to the screen.
 *****************************************************************************/
void Game :: advanceShip()
{	
	if (pShip)
	{
		pShip->advance();
		wrapObject(pShip, minimum, maximum);
	}
}

#define STAR_BORDER 150
/*****************************************************************************
 * ADVANCE ASTEROIDS
 * Update asteroids', stars', and shooting stars' data and wrap them to the
 * screen.
 *****************************************************************************/
void Game :: advanceAsteroids()
{	
	// Advance Asteroids
	vector<Asteroid *> :: iterator itA;
	for (itA = asteroids.begin(); itA != asteroids.end(); ++itA)
	{
		(*itA)->advance();
		wrapObject(*itA, minimum, maximum);
	}
	 
	// Advance shooting stars
	Point starMin(minimum.getX() - STAR_BORDER, minimum.getY() - STAR_BORDER);
	Point starMax(maximum.getX() + STAR_BORDER, maximum.getY() + STAR_BORDER);
	vector<ShootingStar *> :: iterator it4;
	for (it4 = shootingStars.begin(); it4 != shootingStars.end(); ++it4)
	{
		(*it4)->advance();
		wrapObject(*it4, starMin, starMax);
	}
	
	// Advance background stars
	vector<NormalStar *> :: iterator it5;
	for (it5 = normalStars.begin(); it5 != normalStars.end(); ++it5)
	{
		(*it5)->advance();
		wrapObject(*it5, minimum, maximum);
	}
	if (asteroids.size() < NUM_ASTEROIDS)
		for (int i = 0; i < (NUM_ASTEROIDS - asteroids.size()); i++)
			asteroids.push_back(createLargeAsteroid());
}

/*****************************************************************************
 * CREATE LARGE ASTEROID
 * Create a large asteroid and randomize its position and velocity direction
 * on the screen.
 *****************************************************************************/
LargeAsteroid * Game :: createLargeAsteroid()
{
	float x;
	float y;
	
	do
	{
		x = random(topLeft.getX(), bottomRight.getX());
		y = random(bottomRight.getY(), topLeft.getY());
	}
	while (x == pShip->getPoint().getX() && y == pShip->getPoint().getY());
		
	float magnitude = 1.0;
	float angle = random(0.0, 360.0);
	
	LargeAsteroid * pAster = new LargeAsteroid;
	pAster->setMagnitude(magnitude);
	pAster->setAngle(angle);
	pAster->setX(x);
	pAster->setY(y);
	
	return pAster;
}

/*****************************************************************************
 * CREATE MEDIUM ASTEROID
 * Create a medium asteroid located at the destroyed large asteroid's position,
 * and set its velocity vector dependent on the large asteroid's velocity.
 *
 * INPUT:	aster		(Large) asteroid that was destroyed
 *				ddx		Change in new velocity's dx
 *				ddy		Change in new velocity's dy
 *****************************************************************************/
MediumAsteroid * Game :: createMediumAsteroid(Asteroid * aster,
															float ddx, float ddy)
{
	Point    point    = aster->getPoint();
	Velocity velocity = aster->getVelocity();
	
	velocity.addDx(ddx);
	velocity.addDy(ddy);
	
	return new MediumAsteroid(point, velocity);
}

/*****************************************************************************
 * CREATE SMALL ASTEROID
 * Create a small asteroid located at the destroyed asteroid's position, and
 * set its velocity vector dependent on the asteroid's velocity. (The old
 * asteroid could be either medium or large.)
 *
 * INPUT:	aster		(Large or medium) asteroid that was destroyed
 *				ddx		Change in new velocity's dx
 *				ddy		Change in new velocity's dy
 *****************************************************************************/
SmallAsteroid * Game :: createSmallAsteroid(Asteroid * aster,
														  float ddx, float ddy)
{
	Point    point    = aster->getPoint();
	Velocity velocity = aster->getVelocity();
	
	velocity.addDx(ddx);
	velocity.addDy(ddy);
	
	return new SmallAsteroid(point, velocity);
}

/*****************************************************************************
 * WRAP OBJECT
 * Wrap an object to the screen based on the minimum and maximum points.
 * If the object goes off the left edge, place it at the right edge and
 * invert its vertical position.
 * If the object goes off the right edge, place it at the left edge and
 * invert its vertical position.
 * If the object goes off the top edge, place it at the bottom edge and
 * invert its horizontal position.
 * If the object goes off the bottom edge, place it at the top edge and
 * invert its horizontal position.
 *
 * INPUT:		pObj		Moveable object to wrap
 *					min		Point containing minimum x and y values.
 *					max		Point containing maximum x and y values.
 *****************************************************************************/
void Game :: wrapObject(Moveable * pObj, const Point & min, const Point & max)
{
	/*********************
	 * Wrap Horizontally *
	 *********************/
	
	// Right edge
	if (pObj->getPoint().getX() + pObj->getVelocity().getDx() > max.getX())
	{
		pObj->setX(min.getX());
		pObj->setY(-pObj->getPoint().getY());
	}
	// Left edge
	else if (pObj->getPoint().getX() + pObj->getVelocity().getDx() < min.getX())
	{
		pObj->setX(max.getX());
		pObj->setY(-pObj->getPoint().getY());
	}
	
	/*******************
	 * Wrap Vertically *
	 *******************/
	
	// Top edge
	if (pObj->getPoint().getY() + pObj->getVelocity().getDy() > max.getY())
	{
		pObj->setY(min.getY());
		pObj->setX(-pObj->getPoint().getX());
	}
	// Bottom edge
	else if (pObj->getPoint().getY() + pObj->getVelocity().getDy() < min.getY())
	{
		pObj->setY(max.getY());
		pObj->setX(-pObj->getPoint().getX());
	}
}

#define BIG_ROCK_TYPE      1
#define MEDIUM_ROCK_TYPE   2
#define SMALL_ROCK_TYPE    3
#define SCORE_TO_NEW_LIFE 50
/*****************************************************************************
 * HANDLE COLLISIONS
 * Destroy objects that will cross paths (using the closest distance function).
 *****************************************************************************/
void Game :: handleCollisions()
{
	vector<Asteroid *> newAsteroids;
	vector<Bullet *>    :: iterator itB;
	vector<Asteroid *>  :: iterator itA;	// For current asteroids
	vector<Asteroid *>  :: iterator itN;	// For new asteroids
	
	// Check collision with each asteroid
	for (itA = asteroids.begin(); itA != asteroids.end(); ++itA)
	{
		bool hit = false;
		// Vs. Bullets
		for (itB = bullets.begin(); itB != bullets.end(); ++itB)
		{
			if (getClosestDistance(**itA, **itB) <=
				 (*itA)->getRadius() + (*itB)->getRadius())
			{
				hit = true;
				(*itB)->kill();
			}
		}
		
		// Vs. Shockwave
		if (pShockwave)
		{
			if (getClosestDistance(**itA, *pShockwave) <=
				 (*itA)->getRadius() + (pShockwave)->getRadius())
				hit = true;
		}
			
		// Vs. Ship
		if (pShip)
		{
			if (getClosestDistance(**itA, *pShip) <=
				 (*itA)->getRadius() + pShip->getRadius())
			{
				pShip->kill();
				(*itA)->kill();
			}
		}
		
		// For every hit, add new asteroids (as applicable)
		if (hit && (*itA))
		{
			int rockType = (*itA)->getType();
			switch (rockType)
			{
				case BIG_ROCK_TYPE:
					newAsteroids.push_back(createMediumAsteroid(*itA, 0.0, 1.0));
					newAsteroids.push_back(createMediumAsteroid(*itA, 0.0, -1.0));
					newAsteroids.push_back(createSmallAsteroid(*itA, 2.0, 0.0));
					break;
					
				case MEDIUM_ROCK_TYPE:
					newAsteroids.push_back(createSmallAsteroid(*itA, 3.0, 0.0));
					newAsteroids.push_back(createSmallAsteroid(*itA, -3.0, 0.0));
					break;
			}
			
			// Kill the object
			(*itA)->kill();
			// Increase the score
			score++;
			// Update the hit-miss ratio
			hitRatio = (float)score / (float)shots;
			// Increase lives as applicable
			if ((score % SCORE_TO_NEW_LIFE) == 0)
				lives++;
		}
	}
	
	// Take all new asteroids and put them in general asteroids vector
	for (itN = newAsteroids.begin(); itN != newAsteroids.end(); ++itN)
	{
		switch ((*itN)->getType())
		{
			case BIG_ROCK_TYPE:
				asteroids.push_back(createLargeAsteroid());
				break;
			case MEDIUM_ROCK_TYPE:
				asteroids.push_back(new MediumAsteroid(*itN));
				break;
			case SMALL_ROCK_TYPE:
				asteroids.push_back(new SmallAsteroid(*itN));
				break;
		}
		
		delete (*itN);
		(*itN) = NULL;
		newAsteroids.erase(itN);
		--itN;
	}
}

/*****************************************************************************
 * CLEAN UP ZOMBIES
 * Delete all moveable objects that are no longer alive.
 *****************************************************************************/
void Game :: cleanUpZombies()
{
	// Clean up dead ship
	if (pShip && !(pShip->isAlive()))
	{
		delete pShip;
		if (lives > 0)
		{
			pShip = new Ship;
			lives--;
		}
		else
			pShip = NULL;
	}
		
	// Clean up dead bullets
	vector<Bullet *> :: iterator it0;
	for (it0 = bullets.begin(); it0 != bullets.end(); ++it0)
	{
		if ((*it0) && !((*it0)->isAlive()))
		{
			delete (*it0);
			(*it0) = NULL;
			bullets.erase(it0);
			--it0;
		}
	}
	
	// Clean up dead shockwave
	if (pShockwave && !(pShockwave->isAlive()))
	{
		delete pShockwave;
		pShockwave = NULL;
	}
	
	// Clean up dead asteroids
	vector<Asteroid *> :: iterator itA;
	for (itA = asteroids.begin(); itA != asteroids.end(); ++itA)
	{
		if ((*itA) && !((*itA)->isAlive()))
		{
			delete (*itA);
			(*itA) = NULL;
			asteroids.erase(itA);
			--itA;
		}
	}
	 
	// Clean up dead shooting stars
	vector<ShootingStar *> :: iterator it4;
	for (it4 = shootingStars.begin(); it4 != shootingStars.end(); ++it4)
	{
		if (*it4 && !((*it4)->isAlive()))
		{
			delete (*it4);
			(*it4) = NULL;
			shootingStars.erase(it4);
			--it4;
		}
	}
	
	// Clean up dead background stars
	vector<NormalStar *> :: iterator it5;
	for (it5 = normalStars.begin(); it5 != normalStars.end(); ++it5)
	{
		if (*it5 && !((*it5)->isAlive()))
		{
			delete (*it5);
			(*it5) = NULL;
			normalStars.erase(it5);
			--it5;
		}
	}
}

/*****************************************************************************
 * EMPTY VECTORS
 *****************************************************************************/
void Game :: emptyVectors()
{
	while (!bullets.empty())
		bullets.pop_back();
	
	while (!asteroids.empty())
		asteroids.pop_back();
	 
	while (!shootingStars.empty())
		shootingStars.pop_back();
	
	while (!normalStars.empty())
		normalStars.pop_back();
}