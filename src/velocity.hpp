// velocity.hpp

#ifndef VELOCITY_HPP
#define VELOCITY_HPP

/*****************************************************************************
 * VELOCITY
 *****************************************************************************/

class Velocity
{
  private:
   float magnitude;
	float angle;

  public:
	// Constructors
   Velocity();
	Velocity(const Velocity & velocity);
   Velocity(float magnitude, float angle);
	Velocity& operator=(const Velocity&) = default;

	// Accessors
	float getMagnitude() const;
	float getAngle()     const;
   float getDx()        const;
   float getDy()        const;
	
	// Mutators
   void  setPolar(float magnitude, float angle);
	void  setMagnitude(float magnitude);
	void  setAngle(float angle);
	void  setRectangular(float dx, float dy);
	void  addDx(float ddx);
	void  addDy(float ddy);
	void  subDx(float ddx);
	void  subDy(float ddy);
	
	// Rotators
	void  rotateClockwise(float dtheta);
	void  rotateCounterClockwise(float dtheta);
	void  addMagnitude(float dmag);
	void  subMagnitude(float dmag);
};

// Overloaded Operators
Velocity   operator +  (const Velocity & lhs, const Velocity & rhs);
Velocity   operator +  (const Velocity & lhs, float rhs);
Velocity   operator -  (const Velocity & lhs, const Velocity & rhs);
Velocity   operator -  (const Velocity & lhs, float rhs);
Velocity & operator += (Velocity & lhs, const Velocity & rhs);
Velocity & operator += (Velocity & lhs, float rhs);
Velocity & operator -= (Velocity & lhs, const Velocity & rhs);
Velocity & operator -= (Velocity & lhs, float rhs);
bool       operator == (const Velocity & lhs, const Velocity & rhs);
bool       operator == (const Velocity & lhs, float rhs);
bool       operator != (const Velocity & lhs, const Velocity & rhs);
bool       operator != (const Velocity & lhs, float rhs);

#endif