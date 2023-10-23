#include "ship.hpp"
#include "point.hpp"
#include "velocity.hpp"
#include "uiDraw.hpp"

/*****************************************************************************
 * SHIP CLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Set alive.
 * Initialize frame count to 0.
 * Set collision radius as 10.
 * Set thrust off (don't show flames).
 * Set rotation at 0 degrees.
 * Set velocity as (0, 0).
 *****************************************************************************/
Ship :: Ship()
{
	alive = true;
	setFramesAlive(0);
	setRadius(10);
	thrust = THRUST_OFF;
	setRotation(0.0);
	velocity.setMagnitude(0.0);
	velocity.setAngle(rotation);
}

/*****************************************************************************
 * THRUST UP
 * Increase magnitude of speed until at maximum and move ship forward in the
 * direction it is pointing (modify velocity vector gradually).
 *****************************************************************************/
void Ship :: thrustUp()
{
	thrust = THRUST_UP;

	velocity.addDx(THRUST_AMOUNT * cos(M_PI / 180.0 * rotation));
	velocity.addDy(THRUST_AMOUNT * sin(M_PI / 180.0 * rotation));
	
	if (velocity.getMagnitude() >= MAX_SPEED)
		velocity.setMagnitude(MAX_SPEED);
}

/*****************************************************************************
 * THRUST DOWN
 * Decrease magnitude of speed until at minimum (0).
 *****************************************************************************/
void Ship :: thrustDown()
{
	thrust = THRUST_OFF;
	if (velocity.getMagnitude() <= MIN_SPEED)
		velocity.setMagnitude(MIN_SPEED);
	else
		velocity -= THRUST_AMOUNT;
}

/*****************************************************************************
 * THRUST OFF
 *****************************************************************************/
void Ship :: thrustOff()
{
	thrust = THRUST_OFF;
}

/*****************************************************************************
 * ROTATE CLOCKWISE
 * Decrease angle of rotation.
 *****************************************************************************/
void Ship :: rotateClockwise()
{
	thrustOff();
	rotation -= ROTATE_AMOUNT;
}

/*****************************************************************************
 * ROTATE COUNTER-CLOCKWISE
 * Increase angle of rotation.
 *****************************************************************************/
void Ship :: rotateCounterClockwise()
{
	thrustOff();
	rotation += ROTATE_AMOUNT;
}

/*****************************************************************************
 * SET ROTATION
 *
 * INPUT:	rotation		Angle of rotation (for drawing)
 *****************************************************************************/
void Ship :: setRotation(float rotation)
{
	this->rotation = rotation;
}

/*****************************************************************************
 * GET ROTATION
 *****************************************************************************/
float Ship :: getRotation()
{
	return rotation;
}

/*****************************************************************************
 * HAS THRUST
 *****************************************************************************/
bool Ship :: hasThrust()
{
	return (thrust != 0);
}

/*****************************************************************************
 * DRAW
 * Use thrust to draw flames and rotation to point the ship.
 *****************************************************************************/
void Ship :: draw()
{	
	// Draw the ship red
	Color color(1.0, 0.0, 0.0);
	drawShip(getPoint(), rotation - 90.0, color, thrust);
}
