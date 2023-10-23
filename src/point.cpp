/*****************************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich, James D. Downer
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 *****************************************************************************/

#include "point.hpp"
#include <cassert>

/*****************************************************************************
 * POINT CLASS
 *****************************************************************************/

/*****************************************************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position.
 *
 * INPUT:	x		X-coordinate
 *				y		Y-coordinate
 *****************************************************************************/
Point::Point(float x, float y) : x(0.0), y(0.0)
{
   setX(x);
   setY(y);
}

/*****************************************************************************
 * POINT : SET X
 * Set the x position if the value is within range.
 *
 * INPUT:	x		X-coordinate
 *****************************************************************************/
void Point::setX(float x)
{
   this->x = x;
}

/*****************************************************************************
 * POINT : SET Y
 * Set the y position if the value is within range.
 *
 * INPUT:	y		Y-coordinate
 *****************************************************************************/
void Point::setY(float y)
{
   this->y = y;
} 

/*****************************************************************************
 * POINT insertion
 * Display coordinates on the screen.
 *
 * INPUT:	out		Output stream
 *				pt			Point object
 *****************************************************************************/
std::ostream & operator << (std::ostream & out, const Point & pt)
{
   out << "(" << pt.getX() << ", " << pt.getY() << ")";
   return out;
}

/*****************************************************************************
 * POINT extraction
 * Prompt for coordinates.
 *
 * INPUT:	in			Input stream
 *				pt			Point object
 *****************************************************************************/
std::istream & operator >> (std::istream & in, Point & pt)
{
   float x;
   float y;
   in >> x >> y;

   pt.setX(x);
   pt.setY(y);

   return in;
}
   
/*****************************************************************************
 * NON-MEMBER OPERATORS
 *****************************************************************************/

/*****************************************************************************
 * ADD (Velocity to Point)
 *
 * INPUT:	lhs	Point
 *				rhs	Velocity
 *****************************************************************************/
Point operator + (const Point & lhs, const Velocity & rhs)
{
	Point res;
	
	res.setX(lhs.getX() + rhs.getDx());
	res.setY(lhs.getY() + rhs.getDy());
	
	return res;
}

/*****************************************************************************
 * SUBTRACT (Velocity from Point)
 *
 * INPUT:	lhs	Point
 *				rhs	Velocity
 *****************************************************************************/
Point operator - (const Point & lhs, const Velocity & rhs)
{
	Point res;
	
	res.setX(lhs.getX() - rhs.getDx());
	res.setY(lhs.getY() - rhs.getDy());
	
	return res;
}

/*****************************************************************************
 * APPEND (from Velocity)
 * 
 * INPUT:	lhs	Point
 *				rhs	Velocity
 *****************************************************************************/
Point & operator += (Point & lhs, const Velocity & rhs)
{
	lhs.addX(rhs.getDx());
	lhs.addY(rhs.getDy());
	
	return lhs;
}

/*****************************************************************************
 * TRUNCATE (from Velocity)
 *
 * INPUT:	lhs	Point
 *				rhs	Velocity
 *****************************************************************************/
Point & operator -= (Point & lhs, const Velocity & rhs)
{
	lhs.addX(0.0 - rhs.getDx());
	lhs.addY(0.0 - rhs.getDy());
	
	return lhs;
}
