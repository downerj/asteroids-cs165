// bullet.cpp

#include "bullet.hpp"
#include "uiDraw.hpp"

/*****************************************************************************
 * BULLET CLASS
 *****************************************************************************/

/*****************************************************************************
 * DEFAULT CONSTRUCTOR
 * Set radius to 1.
 * Set color to white (color number 14 / hex color 0xffffff).
 * Set object alive.
 # Set frame count to 0.
 *****************************************************************************/

Bullet :: Bullet()
{
	setRadius(1);
	colorNumber = 14; // white
	alive = true;
	setFramesAlive(0);
}

#define BULLET_RADIUS 2
#define FADING       80.0
/*****************************************************************************
 * DRAW
 * Dim bullet color depending on how long it's been alive.
 *****************************************************************************/
void Bullet::draw()
{
	Color color(colorNumber);
	
	color.setRed(color.getRed()     - (getFramesAlive() / FADING));
	color.setGreen(color.getGreen() - (getFramesAlive() / FADING));
	color.setBlue(color.getBlue()   - (getFramesAlive() / FADING));
	
	if (isAlive())
	{
		drawDot(getPoint(), color);
	}
}

/*****************************************************************************
 * FIRE
 * 
 * INPUT:	point		 Point to start at
 *				angle		 Angle of velocity vector
 *				magnitude Magnitude of velocity vector
 *****************************************************************************/
void Bullet::fire(const Point & point, float angle, float magnitude)
{
	setPoint(point);
	setMagnitude(magnitude);
	setAngle(angle);
}

/*****************************************************************************
 * GET COLOR NUMBER (0 to 14)
 *****************************************************************************/
int Bullet :: getColorNumber()
{
	return colorNumber;
}

/*****************************************************************************
 * SET COLOR NUMBER
 *	Set object's color based on number 0-14.
 *
 * INPUT:	colorNumber		Integer of color
 *****************************************************************************/
void Bullet :: setColorNumber(int colorNumber)
{
	this->colorNumber = colorNumber;
}

/*****************************************************************************
 * SHOCKWAVE CLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Initialize radius to 10 (for collision).
 * Set speed to 10 px/frame.
 * Set a random color number (between red 0xff0000 and pink 0xff007f).
 * Set alive.
 * Set initial frame count to 0.
 *****************************************************************************/
Shockwave :: Shockwave()
{
	setRadius(10);
	setSpeed(10);
	setColorNumber(random(1, 13));
	alive = true;
	setFramesAlive(0);
}

#define SHOCKWAVE_THICKNESS 20
#define STROBE_PERIOD        2
#define FADE_PERIOD        500.0
/*****************************************************************************
 * DRAW
 * Draw the shockwave as a collection of concentric circles.
 * Each time the shockwave is drawn to the screen, reset its color to a random
 * number.
 *****************************************************************************/
void Shockwave :: draw()
{
	Color color(random(1, 13));
	
	color.setRed(color.getRed() - radius / FADE_PERIOD);
	color.setGreen(color.getGreen() - radius / FADE_PERIOD);
	color.setBlue(color.getBlue() - radius / FADE_PERIOD);
	
	for (unsigned int i = 0; i < SHOCKWAVE_THICKNESS; i++)
	{
		if (isAlive())
			drawCircle(getPoint(), radius + i, color);
	}
}

/*****************************************************************************
 * FIRE
 * Set the shockwave's center point.
 * Set the shockwave speed.
 *
 * INPUT:	point		Center point of circles
 *****************************************************************************/
void Shockwave :: fire(const Point & point)
{
	setPoint(point);
	this->speed = speed;
}

/*****************************************************************************
 * ADVANCE
 * Update the frame count and radius.
 *****************************************************************************/
void Shockwave :: advance()
{
	if (alive)
	{
		framesAlive++;
		radius += speed;
	}
}

/*****************************************************************************
 * GET MAX RADIUS
 *****************************************************************************/
int Shockwave :: getMaxRadius()
{
	return maxRadius;
}

/*****************************************************************************
 * GET SPEED
 *****************************************************************************/
int Shockwave :: getSpeed()
{
	return speed;
}

/*****************************************************************************
 * SET MAX RADIUS
 *
 * INPUT		maxRadius		Maximum radius (e.g. shockwave thickness)
 *****************************************************************************/
void Shockwave :: setMaxRadius(int maxRadius)
{
	this->maxRadius = maxRadius;
}

/*****************************************************************************
 * SET SPEED
 *
 * INPUT		speed		Speed of the shockwave (px/frame)
 *****************************************************************************/
void Shockwave :: setSpeed(int speed)
{
	this->speed = speed;
}