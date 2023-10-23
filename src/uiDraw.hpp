/*****************************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich, James D. Downer
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 *****************************************************************************/

#ifndef UI_DRAW_HPP
#define UI_DRAW_HPP

#include <string>       // To display text on the screen
#include <cmath>        // for M_PI, sin() and cos()
#include <algorithm>    // used for min() and max()
#include "point.hpp"    // Where things are drawn
#include "color.hpp"    // What to color the things with
using std::string;
using std::min;
using std::max;

/*****************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *****************************************************************************/
void drawDigit(const Point & topLeft, const char & digit);

/*****************************************************************************
 * DRAW DIGIT (Colored)
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *****************************************************************************/
void drawDigit(const Point & topLeft, const char & digit, const Color & color);

/*****************************************************************************
 * DRAW NUMBER
 * Display an integer on the screen using the 7-segment method
 *****************************************************************************/
void drawNumber(const Point & topLeft, int number);

/*****************************************************************************
 * DRAW NUMBER (Colored)
 * Display an integer on the screen using the 7-segment method
 *****************************************************************************/
void drawNumber(const Point & topLeft, int number, const Color & color);

/*****************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *****************************************************************************/
void drawText(const Point & topLeft, const char * text);

/*****************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *****************************************************************************/
void rotate(Point & point, const Point & origin, int rotation = 0);

/*****************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 *****************************************************************************/
void drawRect(const Point & center, int width, int height, int rotation);

/*****************************************************************************
 * DRAW RECTANGLE (Colored)
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 *****************************************************************************/
void drawRect(const Point & center, int width, int height, int rotation,
              const Color & color);

/*****************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *****************************************************************************/
void drawCircle(const Point & center, int radius);

/*****************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius)
 * using the RGB colors (each from 0.0 to 1.0);
 *****************************************************************************/
void drawCircle(const Point & center, int radius, const Color & color);

/*****************************************************************************
 * DRAW POLYGON
 * Draw a polygon from a given location (center) of a given size (radius).
 *****************************************************************************/
void drawPolygon(const Point & center,
                 int radius = 20,
                 int points = 4,
                 int rotation = 0);

/*****************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *****************************************************************************/
void drawLine(const Point & begin, const Point & end, const Color & color);

/*****************************************************************************
 * DRAW Lander
 * Draw a moon-lander spaceship on the screen at a given point
 *****************************************************************************/
void drawLander(const Point & point);

/*****************************************************************************
 * DRAW Lander (Colored)
 * Draw a moon-lander spaceship on the screen at a given point
 *****************************************************************************/
void drawLander(const Point & point, const Color & color);

/*****************************************************************************
 * DRAW Lander Flame
 * Draw the flames coming out of a moonlander for thrust
 *****************************************************************************/
void drawLanderFlames(const Point & point, 
                      bool bottom,
                      bool left,
                      bool right);

/*****************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *****************************************************************************/
void drawDot(const Point & point);

/*****************************************************************************
 * DRAW DOT (Colored)
 * Draw a single colored point on the screen, 2 pixels by 2 pixels
 *****************************************************************************/
void drawDot(const Point & point, const Color & color);

/*****************************************************************************
 * DRAW Sacred Bird
 * Draw the bird on the screen
 *****************************************************************************/
void drawSacredBird(const Point & center, float radius);

/*****************************************************************************
 * DRAW Tough Bird
 * Draw a tough bird on the screen
 *****************************************************************************/
void drawToughBird(const Point & center, float radius, int hits,
						 const Color & color);

/*****************************************************************************   
 * DRAW Ship                                                                
 * Draw the spaceship on the screen                                         
 *****************************************************************************/
void drawShip(const Point & point, int rotation, const Color & color,
				  int thrust = 0);

/*****************************************************************************
 * DRAW * ASTEROID
 ****************************************************************************/
void drawSmallAsteroid( const Point & point, int rotation,
							   const Color & color);
void drawMediumAsteroid(const Point & point, int rotation,
								const Color & color);
void drawLargeAsteroid( const Point & point, int rotation,
							   const Color & color);

/*****************************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 *****************************************************************************/
int    random(int    min, int    max);
double random(double min, double max);

#endif // UI_DRAW_H
