// color.h

#ifndef COLOR_HPP
#define COLOR_HPP

/*****************************************************************************
 * COLOR
 * Emulates an RGB color with R, G, and B values each between 0.0 and 1.0.
 *****************************************************************************/

class Color
{
private:
	float red;
	float green;
	float blue;
	
public:
	Color();
	Color(float red, float green, float blue);
	Color(int colorNumber);
	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	void  setRed(float red);
	void  setGreen(float green);
	void  setBlue(float blue);
};

#endif