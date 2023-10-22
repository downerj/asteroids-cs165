#ifndef ship_hpp
#define ship_hpp

#include "moveable.hpp"

#define SHIP_SIZE    10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#define THRUST_OFF	 0
#define THRUST_UP     1
#define MAX_SPEED     5
#define MIN_SPEED     0

/*****************************************************************************
 * SHIP : MOVEABLE
 * This is a simple ship (that the user can control).
 *****************************************************************************/
 
class Ship : public Moveable
{
private:
	int   thrust;
	float rotation; // Drawing rotation (and for firing bullets)
						 // Separate from velocity angle of movement
	
public:
	// Constructor
	Ship();
	
	// Destructor
	~Ship() { }
	
	// Accessors
	float getRotation(); 
	bool  hasThrust();
	
	// Mutator
	void setRotation(float rotation);
	
	// Movement & Rotation
	void thrustUp();
	void thrustDown();
	void thrustOff();
	void rotateClockwise();
	void rotateCounterClockwise();
	
	// Draw
	virtual void draw();
};

#endif /* ship_hpp */
