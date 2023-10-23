// velocity.cpp

#include <iostream>
#include <cmath>
using namespace std;

#include "velocity.hpp"

#define deg2rad(value) ((double)(M_PI / 180.0) * value)
#define rad2deg(value) ((double)((value * 180.0) / M_PI))

/*****************************************************************************
 * VELOCITY CLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Set as (0, 0).
 *****************************************************************************/
Velocity :: Velocity()
{
	magnitude = 0.0;
	angle     = 0.0;
}

/*****************************************************************************
 * Copy constructor
 * 
 * INPUT:	velocity		Old velocity
 *****************************************************************************/
Velocity :: Velocity(const Velocity & velocity)
{
	setMagnitude(velocity.getMagnitude());
	setAngle(velocity.getAngle());
}

/*****************************************************************************
 * Non-default Constructor
 *
 * INPUT:	magnitude	Magnitude of velocity
 *				angle			Direction of velocity
 *****************************************************************************/
Velocity :: Velocity(float magnitude, float angle)
{
	setMagnitude(magnitude);
	setAngle(angle);
}

/*****************************************************************************
 * GET MAGNITUDE
 *****************************************************************************/
float Velocity :: getMagnitude() const
{
	return magnitude;
}

/*****************************************************************************
 * GET ANGLE
 *****************************************************************************/
float Velocity :: getAngle() const
{
	return angle;
}

/*****************************************************************************
 * GET DX
 *****************************************************************************/
float Velocity :: getDx() const
{
	return magnitude * cos(deg2rad(angle));
}

/*****************************************************************************
 * GET DY
 *****************************************************************************/
float Velocity :: getDy() const
{
	return magnitude * sin(deg2rad(angle));
}

/*****************************************************************************
 * SET POLAR
 *
 * INPUT:	magnitude	Magnitude of velocity
 *				angle			Direction of velocity
 *****************************************************************************/
void Velocity :: setPolar(float magnitude, float angle)
{
	setMagnitude(magnitude);
	setAngle(angle);
}

/*****************************************************************************
 * SET MAGNITUDE
 *
 * INPUT:	magnitude	Magnitude of velocity
 *****************************************************************************/
void Velocity :: setMagnitude(float magnitude)
{
	this->magnitude = magnitude;
}

/*****************************************************************************
 * SET ANGLE
 *
 * INPUT:	angle		Direction of velocity
 *****************************************************************************/
void Velocity :: setAngle(float angle)
{
	this->angle = angle;
}

/*****************************************************************************
 * SET RECTANGULAR
 * 
 * INPUT:	dx		Dx value
 *				dy    Dy value
 *****************************************************************************/
void Velocity :: setRectangular(float dx, float dy)
{
	setMagnitude(sqrt(dx * dx + dy * dy));
	setAngle(rad2deg(atan2(dy, dx)));
}

/*****************************************************************************
 * ADD DX
 *
 *	INPUT:	ddx	Change in Dx value (positive)
 *****************************************************************************/
void Velocity :: addDx(float ddx)
{
	float oldDx = getDx();
	float oldDy = getDy();
	float newDx = oldDx + ddx;
	float newDy = oldDy;
	
	setRectangular(newDx, newDy);
}

/*****************************************************************************
 * ADD DY
 *
 * INPUT:	ddy	Change in Dy value (positive)
 *****************************************************************************/
void Velocity :: addDy(float ddy)
{
	float oldDx = getDx();
	float oldDy = getDy();
	float newDx = oldDx;
	float newDy = oldDy + ddy;
	
	setRectangular(newDx, newDy);
}

/*****************************************************************************
 * SUB DX
 *
 * INPUT:	ddx	Change in Dx value (positive -> converted to negative)
 *****************************************************************************/
void Velocity :: subDx(float ddx)
{
	float oldDx = getDx();
	float oldDy = getDy();
	float newDx = oldDx - ddx;
	float newDy = oldDy;
	
	setRectangular(newDx, newDy);
}

/*****************************************************************************
 * SUB DY
 * 
 * INPUT:	ddy	Change in Dy value (positive -> converted to negative)
 *****************************************************************************/
void Velocity :: subDy(float ddy)
{
	float oldDx = getDx();
	float oldDy = getDy();
	float newDx = oldDx;
	float newDy = oldDy - ddy;
	
	setRectangular(newDx, newDy);
}

/*****************************************************************************
 * ROTATE CLOCKWISE
 *
 * INPUT:	dtheta	Change in direction (negatively)
 *****************************************************************************/
void Velocity :: rotateClockwise(float dtheta)
{
	setAngle(getAngle() - dtheta);
}

/*****************************************************************************
 * ROTATE COUNTER-CLOCKWISE
 *
 * INPUT:	dtheta	Change in direction (positively)
 *****************************************************************************/
void Velocity :: rotateCounterClockwise(float dtheta)
{
	setAngle(getAngle() + dtheta);
}

/*****************************************************************************
 * ADD MAGNITUDE
 *
 * INPUT:	dmag		Change in magnitude (positive)
 *****************************************************************************/
void Velocity :: addMagnitude(float dmag)
{
	setMagnitude(getMagnitude() + dmag);
}

/*****************************************************************************
 * SUB MAGNITUDE
 * INPUT:	dmag		Change in magnitude (positive -> converted to negative)
 *****************************************************************************/
void Velocity :: subMagnitude(float dmag)
{
	setMagnitude(getMagnitude() - dmag);
}

/*****************************************************************************
 * NON-MEMBER OPERATORS
 *****************************************************************************/

/*****************************************************************************
 * ADD
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Velocity2
 *****************************************************************************/
Velocity operator + (const Velocity & lhs, const Velocity & rhs)
{
	Velocity res;
	
	res.setRectangular(lhs.getDx() + rhs.getDx(),
					       lhs.getDy() + rhs.getDy());
	
	return res;
}

/*****************************************************************************
 * ADD
 *
 * INPUT:	lhs	Velocity1
 *				rhs   Magnitude of Velocity2
 *****************************************************************************/
Velocity operator + (const Velocity & lhs, float rhs)
{
	Velocity res;
	
	res.setMagnitude(lhs.getMagnitude());
	res.addMagnitude(rhs);
	res.setAngle(lhs.getAngle());
	
	return res;
}

/*****************************************************************************
 * SUBTRACT
 * 
 * INPUT:	lhs	Velocity1
 *				rhs	Velocity2
 *****************************************************************************/
Velocity operator - (const Velocity & lhs, const Velocity & rhs)
{
	Velocity res;
	
	res.setRectangular(lhs.getDx() - rhs.getDx(),
					       lhs.getDy() - rhs.getDy());
	
	return res;
}

/*****************************************************************************
 * SUBTRACT
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Magnitude of Velocity2
 *****************************************************************************/
Velocity operator - (const Velocity & lhs, float rhs)
{
	Velocity res;
	
	res.setMagnitude(lhs.getMagnitude());
	res.subMagnitude(rhs);
	res.setAngle(lhs.getAngle());
	
	return res;
}

/*****************************************************************************
 * APPEND
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Velocity2
 *****************************************************************************/
Velocity & operator += (Velocity & lhs, const Velocity & rhs)
{
	lhs.setRectangular(lhs.getDx() + rhs.getDx(),
							 lhs.getDy() + rhs.getDy());
	 
	return lhs;
}

/*****************************************************************************
 * APPEND
 * 
 * INPUT:	lhs	Velocity1
 *				rhs	Magnitude of Velocity2
 *****************************************************************************/
Velocity & operator += (Velocity & lhs, float rhs)
{
	lhs.addMagnitude(rhs);
	lhs.setAngle(lhs.getAngle());
	
	return lhs;
}

/*****************************************************************************
 * TRUNCATE
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Velocity2
 *****************************************************************************/
Velocity & operator -= (Velocity & lhs, const Velocity & rhs)
{
	lhs.setRectangular(lhs.getDx() - rhs.getDx(),
					       lhs.getDy() - rhs.getDy());
	 
	return lhs;
}

/*****************************************************************************
 * TRUNCATE
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Magnitude of Velocity2
 *****************************************************************************/
Velocity & operator -= (Velocity & lhs, float rhs)
{
	lhs.subMagnitude(rhs);
	lhs.setAngle(lhs.getAngle());
	
	return lhs;
}

/*****************************************************************************
 * COMPARE
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Velocity2
 *****************************************************************************/
bool operator == (const Velocity & lhs, const Velocity & rhs)
{
	return (lhs.getMagnitude() == rhs.getMagnitude()) &&
	       (lhs.getAngle()     == rhs.getAngle());
}

/*****************************************************************************
 * COMPARE
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Magnitude of Velocity2
 *****************************************************************************/
bool operator == (const Velocity & lhs, float rhs)
{
	return (lhs.getMagnitude() == rhs);
}

/*****************************************************************************
 * CONTRAST
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Velocity2
 *****************************************************************************/
bool operator != (const Velocity & lhs, const Velocity & rhs)
{
	return (lhs.getMagnitude() != rhs.getMagnitude()) ||
			 (lhs.getAngle()     != rhs.getAngle());
}

/*****************************************************************************
 * CONTRAST
 *
 * INPUT:	lhs	Velocity1
 *				rhs	Magnitude of Velocity2
 *****************************************************************************/
bool operator != (const Velocity & lhs, float rhs)
{
	return (lhs.getMagnitude() != rhs);
}
