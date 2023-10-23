#ifndef STARS_HPP
#define STARS_HPP

#define BIG_ROCK_SIZE     16
#define MEDIUM_ROCK_SIZE   8
#define SMALL_ROCK_SIZE    4
#define SHOOTING_STAR_SIZE 5

#define BIG_ROCK_SPIN      2
#define MEDIUM_ROCK_SPIN   5
#define SMALL_ROCK_SPIN   10
#define SHOOTING_STAR_SPIN 0

#define BIG_ROCK_TYPE      1
#define MEDIUM_ROCK_TYPE   2
#define SMALL_ROCK_TYPE    3

#include "moveable.hpp"
#include "point.hpp"
#include "velocity.hpp"

/*****************************************************************************
 * ASTEROID : MOVEABLE
 * Asteroids for the user to destroy (harmful to ship)
 *****************************************************************************/
class Asteroid : public Moveable
{
private:
	int rotation;	// Rotation around centerpoint (for drawing)
	int spin;		// Spin amount to rotation each frame (defined in subclass)
	int score;
	int type;
	
protected:
	// Special mutators for subclasses
	void setSpin(int spin);
	void setScore(int score);
	void setType(int type);
		
public:
	// Accessors
	int  getRotation();
	int  getSpin();
	int  getScore();
	int  getType();
	
	// Rotator
	void rotate();
	
	// Alternate functions for subclasses
	virtual void advance();
	virtual void draw() = 0;
};

/*****************************************************************************
 * LARGE ASTEROID : ASTEROID
 *****************************************************************************/
class LargeAsteroid : public Asteroid
{
public:
	// Constructors
	LargeAsteroid();
	LargeAsteroid(Asteroid * pAster);
	LargeAsteroid(const Point & point, const Velocity & velocity);
	
	// Destructor
	~LargeAsteroid() { }
	
	// Draw
	virtual void draw();
};

/*****************************************************************************
 * MEDIUM ASTEROID : ASTEROID
 *****************************************************************************/
class MediumAsteroid : public Asteroid
{
public:
	// Constructors
	MediumAsteroid();
	MediumAsteroid(Asteroid * pAster);
	MediumAsteroid(const Point & point, const Velocity & velocity);
	
	// Destructor
	~MediumAsteroid() { }
	
	// Draw
	virtual void draw();	
};

/*****************************************************************************
 * SMALL ASTEROID : ASTEROID
 *****************************************************************************/
class SmallAsteroid : public Asteroid
{
public:
	// Constructors
	SmallAsteroid();
	SmallAsteroid(Asteroid * pAster);
	SmallAsteroid(const Point & point, const Velocity & velocity);
	
	// Destructor
	~SmallAsteroid() { }
	
	// Draw
	virtual void draw();
};

/*****************************************************************************
 * SHOOTING STAR : ASTEROID
 * Background shooting star (with tail)
 *****************************************************************************/
class ShootingStar : public Asteroid
{
public:
	// Constructors
	ShootingStar();
	ShootingStar(const Point & point, const Velocity & velocity);
	
	// Destructor
	~ShootingStar() { }
	
	// Draw
	virtual void draw();
};

/*****************************************************************************
 * NORMAL STAR : ASTEROID
 * Background star
 *****************************************************************************/
class NormalStar : public Asteroid
{
public:
	// Constructors
	NormalStar();
	NormalStar(const Point & point, const Velocity & velocity);
	
	// Destructor
	~NormalStar() { }
	
	// Draw
	virtual void draw();
private:
	float brightness;
};

#endif /* STARS_HPP */
