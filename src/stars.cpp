#include "stars.hpp"
#include "point.hpp"
#include "velocity.hpp"
#include "uiDraw.hpp"
#include "color.hpp"

/*****************************************************************************
 * ASTEROID SUPERCLASS
 *****************************************************************************/

/*****************************************************************************
 * SET SPIN
 * Set spin amount (mutator for rotation); used by subclasses.
 *
 * INPUT:	spin		Integer spin value
 *****************************************************************************/
void Asteroid :: setSpin(int spin)
{
	this->spin = spin;
}

/*****************************************************************************
 * SET SCORE
 * Set score value of asteroid when hit; used by subclasses.
 *
 * INPUT:	socre		Integer score value
 *****************************************************************************/
void Asteroid :: setScore(int score)
{
	this->score = score;
}

/*****************************************************************************
 * SET TYPE
 * Set asteroid type; used by subclasses.
 *		1 Large
 *		2 Medium
 *    3 Small
 *
 * INPUT:	type		Asteroid type
 *****************************************************************************/
void Asteroid :: setType(int type)
{
	this->type = type;
}

/*****************************************************************************
 * GET SPIN
 *****************************************************************************/
int Asteroid :: getSpin()
{
	return spin;
}

/*****************************************************************************
 * GET SCORE
 *****************************************************************************/
int Asteroid :: getScore()
{
	return score;
}

/*****************************************************************************
 * GET ROTATION
 *****************************************************************************/
int Asteroid :: getRotation()
{
	return rotation;
}

/*****************************************************************************
 * GET TYPE
 *****************************************************************************/
int Asteroid :: getType()
{
	return type;
}

/*****************************************************************************
 * ROTATE
 * Update rotation amount using spin value.
 *****************************************************************************/
void Asteroid :: rotate()
{
	rotation += spin;
}

/*****************************************************************************
 * ADVANCE
 * Update position and rotation.
 *****************************************************************************/
void Asteroid :: advance()
{
	move();
	rotate();
}

/*****************************************************************************
 * LARGE ASTEROID SUBCLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Set position to (0, 0).
 * Set velocity to (0, 0).
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *****************************************************************************/
LargeAsteroid :: LargeAsteroid()
{
	setX(0.0);
	setY(0.0);
	setMagnitude(0.0);
	setAngle(0.0);
	setRadius(BIG_ROCK_SIZE);
	setSpin(BIG_ROCK_SPIN);
	setType(BIG_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * Non-default Constructor (based off of previous asteroid)
 * Set position and velocity.
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *
 * INPUT:	pAster		Old Asteroid
 *****************************************************************************/
LargeAsteroid :: LargeAsteroid(Asteroid * pAster)
{
	setPoint(pAster->getPoint());
	setVelocity(pAster->getVelocity());
	setRadius(BIG_ROCK_SIZE);
	setSpin(BIG_ROCK_SPIN);
	setType(BIG_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * Non-default Constructor (based off of position and velocity)
 * Set position and velocity.
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *
 * INPUT:	point		Position
 *				velocity	Velocity
 *****************************************************************************/
LargeAsteroid :: LargeAsteroid(const Point & point, const Velocity & velocity)
{
	setPoint(point);
	setVelocity(velocity);
	setRadius(BIG_ROCK_SIZE);
	setSpin(BIG_ROCK_SPIN);
	setType(BIG_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * DRAW
 *****************************************************************************/
void LargeAsteroid :: draw()
{
	// Draw large asteroids yellow
	Color color(1.0, 1.0, 0.0);
	drawLargeAsteroid(getPoint(), getRotation(), color);
}

/*****************************************************************************
 * MEDIUM ASTEROID SUBCLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Set position to (0, 0).
 * Set velocity to (0, 0).
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *****************************************************************************/
MediumAsteroid :: MediumAsteroid()
{
	setX(0.0);
	setY(0.0);
	setMagnitude(0.0);
	setAngle(0.0);
	setRadius(MEDIUM_ROCK_SIZE);
	setSpin(MEDIUM_ROCK_SPIN);
	setType(MEDIUM_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * Non-default Constructor (based off of previous asteroid)
 * Set position and velocity.
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *
 * INPUT:	pAster		Old Asteroid
 *****************************************************************************/
MediumAsteroid :: MediumAsteroid(Asteroid * pAster)
{
	setPoint(pAster->getPoint());
	setVelocity(pAster->getVelocity());
	setRadius(MEDIUM_ROCK_SIZE);
	setSpin(MEDIUM_ROCK_SPIN);
	setType(MEDIUM_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * Non-default Constructor (based off of position and velocity)
 * Set position and velocity.
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *
 * INPUT:	point		Position
 *				velocity	Velocity
 *****************************************************************************/
MediumAsteroid :: MediumAsteroid(const Point & point, const Velocity & velocity)
{
	setPoint(point);
	setVelocity(velocity);
	setRadius(MEDIUM_ROCK_SIZE);
	setSpin(MEDIUM_ROCK_SPIN);
	setType(MEDIUM_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * DRAW
 *****************************************************************************/
void MediumAsteroid :: draw()
{
	// Draw medium asteroids orange
	Color color(1.0, 0.5, 0.0);
	drawMediumAsteroid(getPoint(), getRotation(), color);
}

/*****************************************************************************
 * SMALL ASTEROID SUBCLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Set position to (0, 0).
 * Set velocity to (0, 0).
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *****************************************************************************/
SmallAsteroid :: SmallAsteroid()
{
	setX(0.0);
	setY(0.0);
	setMagnitude(0.0);
	setAngle(0.0);
	setRadius(SMALL_ROCK_SIZE);
	setSpin(SMALL_ROCK_SPIN);
	setType(SMALL_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * Non-default Constructor (based off of previous asteroid)
 * Set position and velocity.
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *
 * INPUT		pAster		Old Asteroid
 *****************************************************************************/
SmallAsteroid :: SmallAsteroid(Asteroid * pAster)
{
	setPoint(pAster->getPoint());
	setVelocity(pAster->getVelocity());
	setRadius(SMALL_ROCK_SIZE);
	setSpin(SMALL_ROCK_SPIN);
	setType(SMALL_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * Non-default Constructor (based off of position and velocity)
 * Set position and velocity.
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *
 * INPUT:	point		Position
 *				velocity	Velocity
 *****************************************************************************/
SmallAsteroid :: SmallAsteroid(const Point & point, const Velocity & velocity)
{
	setPoint(point);
	setVelocity(velocity);
	setRadius(SMALL_ROCK_SIZE);
	setSpin(SMALL_ROCK_SPIN);
	setType(SMALL_ROCK_TYPE);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * DRAW
 *****************************************************************************/
void SmallAsteroid :: draw()
{
	// Draw small asteroids red
	Color color(1.0, 0.0, 0.0);
	drawSmallAsteroid(getPoint(), getRotation(), color);
}

/*****************************************************************************
 * SHOOTING STAR SUBCLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Set position to (0, 0).
 * Set velocity to (0, 0).
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *****************************************************************************/
ShootingStar :: ShootingStar()
{
	setX(0.0);
	setY(0.0);
	setMagnitude(0.0);
	setAngle(0.0);
	setRadius(SHOOTING_STAR_SIZE);
	setSpin(SHOOTING_STAR_SPIN);
	alive = true;
	setFramesAlive(0);
}

/*****************************************************************************
 * Non-default Constructor (based off of position and velocity)
 * Set position and velocity.
 * Set radius, spin and type.
 * Set alive.
 * Initialize frame count to 0.
 *
 * INPUT:	point		Position
 *				velocity	Velocity
 *****************************************************************************/
ShootingStar :: ShootingStar(const Point & point, const Velocity & velocity)
{
	setPoint(point);
	setVelocity(velocity);
	setRadius(SHOOTING_STAR_SIZE);
	setSpin(SHOOTING_STAR_SPIN);
	alive = true;
	setFramesAlive(0);
}

#define TRAIL_LENGTH  400
#define TRAIL_STRETCH 1
#define FADING        10.0
/*****************************************************************************
 * DRAW
 * Draw a tail (line of dots) with fading brightness.
 *****************************************************************************/
void ShootingStar :: draw()
{
	// Draw the shooting stars dark blue-ish
	// Draw the front tip a lighter blue
	Color color1(0.0, 0.0, 0.75); // Blue-ish
	Color color2(0.0, 0.25, 1.0);  // Blue-cyan-ish
	
	for (unsigned int i = 0; i < TRAIL_LENGTH; i++)
	{
		// Dim the color based on position on the trail
		color1.setRed(color1.getRed() - 
						  ((float)i / ((float)TRAIL_LENGTH * FADING)));
		color1.setGreen(color1.getGreen() -
							 ((float)i / ((float)TRAIL_LENGTH * FADING)));
		color1.setBlue(color1.getBlue() - 
							((float)i / ((float)TRAIL_LENGTH * FADING)));
		
		Point point1;
		point1.setX(getPoint().getX());
		point1.setY(getPoint().getY());
		
		Velocity velocity1;
		velocity1.setMagnitude(getVelocity().getMagnitude() +
									  i * TRAIL_STRETCH);
		velocity1.setAngle(getVelocity().getAngle());
		
		point1.setX(point1.getX() - velocity1.getDx());
		point1.setY(point1.getY() - velocity1.getDy());
	
		if (i > 0)
			drawDot(point1, color1);
		else
			drawDot(point1, color2);
	}
}

/*****************************************************************************
 * NORMAL STAR SUBCLASS
 * Background stars
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Set position to (0, 0).
 * Set velocity to (0, 0).
 * Set radius as 1 (a point).
 * Set spin to 0 (negligible as a point).
 * Set alive.
 * Intialize frame count to 0.
 * Randomize brightness of color.
 *****************************************************************************/
NormalStar :: NormalStar()
{
	setX(0.0);
	setY(0.0);
	setMagnitude(0.0);
	setAngle(0.0);
	setRadius(1);
	setSpin(0);
	alive = true;
	setFramesAlive(0);
	brightness = random(0.0, 2.0);
}

/*****************************************************************************
 * Non-default Constructor
 *	Set point and velocity.
 * Set radius as 1 (a point).
 * Set spin to 0 (negligible as a point).
 * Set alive.
 * Initialize frame count to 0.
 * Randomize brightness of color.
 *
 * INPUT:	point		Position
 *				velocity	Velocity
 *****************************************************************************/
NormalStar :: NormalStar(const Point & point, const Velocity & velocity)
{
	setPoint(point);
	setVelocity(velocity);
	setRadius(1);
	setSpin(0);
	alive = true;
	setFramesAlive(0);
	brightness = random(0.0, 2.0);
}

/*****************************************************************************
 * DRAW
 * Draw white dot on screen with set (randomized) brightness.
 *****************************************************************************/
void NormalStar :: draw()
{
	Color color(1.0 * brightness, 1.0 * brightness, 1.0 * brightness);
	drawDot(getPoint(), color);
}