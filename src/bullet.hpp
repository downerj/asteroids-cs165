// bullet.hpp

#ifndef BULLET_HPP
#define BULLET_HPP

#include "moveable.hpp"
#include "point.hpp"

/*****************************************************************************
 * BULLET : MOVEABLE
 *****************************************************************************/

class Bullet : public Moveable
{	
public:
	// Constructor
	Bullet();
	
	// Destructor
	~Bullet() { }
	
	// Accessor
	int  getColorNumber();
	void setColorNumber(int colorNumber);
	
	// Alternate Functions
	virtual void draw();
	virtual void fire(const Point & point, float angle, float magnitude);
	
private:
	int colorNumber;
};

class Shockwave : public Bullet
{
public:
	// Constructor
	Shockwave();
	
	// Destructor
	~Shockwave() { }
	
	// Accessors
	int getMaxRadius();
	int getSpeed();
	
	// Mutators
	void setMaxRadius(int maxRadius);
	void setSpeed(int speed);
	
	// Alternate Functions
	virtual void draw();
	virtual void fire(const Point & point);
	virtual void advance();
	
private:
	int maxRadius;
	int speed;
};

#endif
