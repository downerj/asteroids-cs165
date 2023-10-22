// color.cpp

#include "color.hpp"

/*****************************************************************************
 * COLOR CLASS
 *****************************************************************************/

/*****************************************************************************
 * Default Constructor
 * Sets a default color of white (0xffffff).
 *****************************************************************************/
Color::Color()
{
	setRed(1.0);
	setGreen(1.0);
	setBlue(1.0);
}

/*****************************************************************************
 * Non-default Constructor (RGB)
 *
 * INPUT:	red	Floating-point number from 0.0 -> 1.0
 *				green	Floating-point number from 0.0 -> 1.0
 *				blue	Floating-point number from 0.0 -> 1.0
 *****************************************************************************/
Color::Color(float red, float green, float blue)
{
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

/*****************************************************************************
 * Non-default Constructor (ColorNumber)
 * 
 * INPUT:	colorNumber			 0 Black		0x000000
 *										 1 Red		0xff0000
 *										 2 Orange	0xff7f00
 *										 3 Yellow	0xffff00
 *										 4				0x7fff00
 *										 5	Green		0x00ff00
 *										 6				0x00ff7f
 *										 7	Cyan		0x00ffff
 *										 8				0x007fff
 *										 9	Blue		0x0000ff
 *										10 Violet	0x7f00ff
 *										11	Magenta	0xff00ff
 *										12	Pink		0xff007f
 *										13	Grey		0x7f7f7f
 *										14	White		0xffffff
 *****************************************************************************/
Color::Color(int colorNumber)
{
	switch (colorNumber)
	{
		// 0x000000
		case 0:
			setRed(0.0);
			setGreen(0.0);
			setBlue(0.0);
			break;
		// 0xff0000
		case 1:
			setRed(1.0);
			setGreen(0.0);
			setBlue(0.0);
			break;
		// 0xff7f00
		case 2:
			setRed(1.0);
			setGreen(0.5);
			setBlue(0.0);
			break;
		// 0xffff00
		case 3:
			setRed(1.0);
			setGreen(1.0);
			setBlue(0.0);
			break;
		// 0x7fff00
		case 4:
			setRed(0.5);
			setGreen(1.0);
			setBlue(0.0);
			break;
		// 0x00ff00
		case 5:
			setRed(0.0);
			setGreen(1.0);
			setBlue(0.0);
			break;
		// 0x00ff7f
		case 6:
			setRed(0.0);
			setGreen(1.0);
			setBlue(0.5);
			break;
		// 0x00ffff
		case 7:
			setRed(0.0);
			setGreen(1.0);
			setBlue(1.0);
			break;
		// 0x007fff
		case 8:
			setRed(0.0);
			setGreen(0.5);
			setBlue(1.0);
			break;
		// 0x0000ff
		case 9:
			setRed(0.0);
			setGreen(0.0);
			setBlue(1.0);
			break;
		// 0x7f00ff
		case 10:
			setRed(0.5);
			setGreen(0.0);
			setBlue(1.0);
			break;
		// 0xff00ff
		case 11:
			setRed(1.0);
			setGreen(0.0);
			setBlue(1.0);
			break;
		// 0xff007f
		case 12:
			setRed(1.0);
			setGreen(0.0);
			setBlue(0.5);
			break;
		// 0x7f7f7f
		case 13:
			setRed(0.5);
			setGreen(0.5);
			setBlue(0.5);
			break;
		// 0xffffff
		case 14:
			setRed(1.0);
			setGreen(1.0);
			setBlue(1.0);
			break;
	}
}

/*****************************************************************************
 * GET RED
 * Returns the red value of the RGB color.
 *****************************************************************************/
float Color::getRed() const
{
	return red;
}

/*****************************************************************************
 * GET GREEN
 * Returns the green value of the RGB color.
 *****************************************************************************/
float Color::getGreen() const
{
	return green;
}

/*****************************************************************************
 * GET BLUE
 * Returns the blue value of the RGB color.
 *****************************************************************************/
float Color::getBlue() const
{
	return blue;
}

/*****************************************************************************
 * SET RED
 * Sets the red value of the RGB color.
 * INPUT:	red		Floating-point value (0.0 -> 1.0)
 *****************************************************************************/
void Color::setRed(float red)
{
	if (red < 0.0)
		this->red = 0.0;
	else if (red > 1.0)
		this->red = 1.0;
	else
		this->red = red;
}

/*****************************************************************************
 * SET GREEN
 * Sets the green value of the RGB color.
 * INPUT:	green		Floating-point value (0.0 -> 1.0)
 *****************************************************************************/
void Color::setGreen(float green)
{
	if (green < 0.0)
		this->green = 0.0;
	else if (green > 1.0)
		this->green = 1.0;
	else
		this->green = green;
}

/*****************************************************************************
 * SET BLUE
 * Sets the blue value of the RGB color.
 * INPUT:	blue		Floating-point value (0.0 -> 1.0)
 *****************************************************************************/
void Color::setBlue(float blue)
{
	if (blue < 0.0)
		this->blue = 0.0;
	else if (blue > 1.0)
		this->blue = 1.0;
	else
		this->blue = blue;
}