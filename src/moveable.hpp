// moveable.hpp

#ifndef MOVEABLE_HPP
#define MOVEABLE_HPP

#include "point.hpp"
#include "velocity.hpp"

/*****************************************************************************
 * MOVEABLE (FLYING OBJECT)
 *****************************************************************************/

class Moveable
{
protected:
	Point    position;
	Velocity velocity;
	bool     alive;
	int      framesAlive;
	void     setFramesAlive(int frames);
	int      radius;
	
	// Function for subclasses
	void     setRadius(int radius) { this->radius = radius; };
	
public:
	// Accessors
	Point    getPoint();
	Velocity getVelocity();
	int      getRadius() { return radius; };
	bool     isAlive();
	int      getFramesAlive();
	
	// Mutators
	void setPoint(const Point & point);
	void setX(float x);
	void setY(float y);
	void setVelocity(const Velocity & velocity);
	void setMagnitude(float magnitude);
	void setAngle(float angle);
	void addDx(float ddx);
	void addDy(float ddy);
	void move();
	void kill();
	virtual void advance();
	
	// Draw
	virtual void draw() = 0;

	virtual ~Moveable() = default;
};

#endif