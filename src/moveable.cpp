// moveable.cpp

#include "moveable.hpp"

/*****************************************************************************
 * MOVEABLE (FLYING OBJECT) CLASS
 *****************************************************************************/

/*****************************************************************************
 * SET FRAMES ALIVE
 * Set current frame count.
 *
 * INPUT:	frames	Integer count of frames that object has been alive.
 *****************************************************************************/
void Moveable :: setFramesAlive(int frames)
{
	framesAlive = frames;
}

/*****************************************************************************
 * GET POINT (Position)
 *****************************************************************************/
Point Moveable :: getPoint()
{
	return position;
}

/*****************************************************************************
 * GET VELOCITY
 *****************************************************************************/
Velocity Moveable :: getVelocity()
{
	return velocity;
}

/*****************************************************************************
 * IS ALIVE
 *****************************************************************************/
bool Moveable :: isAlive()
{
	return alive;
}

/*****************************************************************************
 * GET FRAMES ALIVE
 *****************************************************************************/
int Moveable :: getFramesAlive()
{
	return framesAlive;
}

/*****************************************************************************
 * SET POINT
 *
 * INPUT:	point		Position (x, y)
 *****************************************************************************/
void Moveable :: setPoint(const Point & point)
{
	position = point;
}

/*****************************************************************************
 * SET X (Position)
 *
 * INPUT:	x		Position (x)
 *****************************************************************************/
void Moveable :: setX(float x)
{
	position.setX(x);
}

/*****************************************************************************
 * SET Y (Position)
 *
 * INPUT:	y		Position (y)
 *****************************************************************************/
void Moveable :: setY(float y)
{
	position.setY(y);
}

/*****************************************************************************
 * SET VELOCITY
 *
 * INPUT:	velocity		Polar velocity vector (magnitude, angle)
 *****************************************************************************/
void Moveable :: setVelocity(const Velocity & velocity)
{
	this->velocity = velocity;
}

/*****************************************************************************
 * SET MAGNITUDE
 *
 * INPUT:	magnitude	Magnitude of velocity vector
 *****************************************************************************/
void Moveable :: setMagnitude(float magnitude)
{
	velocity.setMagnitude(magnitude);
}

/*****************************************************************************
 * SET ANGLE
 *
 * INPUT:	angle		Angle of velocity vector
 *****************************************************************************/
void Moveable :: setAngle(float angle)
{
	velocity.setAngle(angle);
}

/*****************************************************************************
 *	ADD DX
 *
 * INPUT:	ddx		Change in velocity's dx
 *****************************************************************************/
void Moveable :: addDx(float ddx)
{
	velocity.addDx(ddx);
}

/*****************************************************************************
 * ADD DY
 *
 * INPUT:	ddy		Change in velocity's dy
 *****************************************************************************/
void Moveable :: addDy(float ddy)
{
	velocity.addDy(ddy);
}

/*****************************************************************************
 * MOVE
 * Update position (x, y) using velocity (dx, dy).
 *****************************************************************************/
void Moveable :: move()
{
	position += velocity;
}

/*****************************************************************************
 * KILL
 *****************************************************************************/
void Moveable :: kill()
{
	alive = false;
}

/*****************************************************************************
 * ADVANCE
 * Update object's frame count and position.
 *****************************************************************************/
void Moveable :: advance()
{
	if (alive)
	{
		framesAlive++;
		move();
	}
}