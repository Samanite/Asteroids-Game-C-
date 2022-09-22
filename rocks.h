#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define BIG_ROCK_TYPE 1
#define MEDIUM_ROCK_TYPE 2
#define SMALL_ROCK_TYPE 3

#define ROCK_SPEED 1

// Define the following classes here:
//   Rock
//   BigRock
//   MediumRock
//   SmallRock
#include<cmath>
#include "flyingObject.h"
#include "point.h"
#include "velocity.h"

/*********************************************
  * ROCK
  * A flying object (life, velocity, point)
  *********************************************/
class Rock : public FlyingObject
{
private:
	int numBigRocks = 0;
	

public:
	//Constructors
	Rock(const Point& point)
	{
		alive = true;
		setPoint(point);
	}

	Rock(const Point& point, const Velocity& velocity, int direction)
	{
		alive = true;
		setPoint(point);
		setVelocity(velocity);
	}

	//Interact
	virtual void draw() = 0;
	virtual int hit() = 0;
	virtual int type() = 0;

};

/*********************************************
  * BIG ROCK
  * A Rock object (life, velocity, point, radius)
  *********************************************/
class BigRock : public Rock
{
private:
	float angle = 60.0;
	int bigRockSpin = 0;
public:
	//Constructor
	BigRock(const Point& point);

	//Interact
	virtual void  draw();
	virtual int hit();
	virtual int type();
};

/*********************************************
  * MEDIUM ROCK
  * A Rock object (life, velocity, point, radius)
  *********************************************/
class MediumRock : public Rock
{
private: 
	int mediumRockSpin = 0;

public:
	//Constructor
	MediumRock(const Point& point, const Velocity & velocity, int direction);

	//Interact
	virtual void  draw();
	virtual int hit();
	virtual int type();

};

/*********************************************
  * SMALL ROCK
  * A Rock object (life, velocity, point, radius)
  *********************************************/
class SmallRock : public Rock
{
private:
	int smallRockSpin = 0;

public:
	//Constructor
	SmallRock(const Point& point, const Velocity& velocity, int direction);

	//Interact
	virtual void  draw();
	virtual int hit();
	virtual int type();

};

#endif // rocks_h 