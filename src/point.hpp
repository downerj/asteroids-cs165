/*****************************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich, James D. Downer
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ****************************************************************************/


#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

#include "velocity.hpp"

/*****************************************************************************
 * POINT
 * A single (x, y) position.  
 *****************************************************************************/
class Point
{
public:
   // Constructors
   Point()            : x(0.0), y(0.0)  {}
   Point(float x, float y);

   // Getters
   float getX()       const { return x;              }
   float getY()       const { return y;              }

   // Setters
   void setX(float x);
   void setY(float y);
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }

private:
   float x;           // Horizontal position
   float y;           // Vertical position
};

// Stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

// Overloaded operators
Point   operator +  (const Point & lhs, const Velocity & rhs);
Point   operator -  (const Point & lhs, const Velocity & rhs);
Point & operator += (Point & lhs, const Velocity & rhs);
Point & operator -= (Point & lhs, const Velocity & rhs);

#endif // POINT_HPP
