#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10
#define ANGLE_START 0
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include<cmath>
#include "flyingObject.h"
#include "point.h"
#include "velocity.h"

/*********************************************
  * SHIP
  * A flying object (life, velocity, point)
  *********************************************/
class Ship : public FlyingObject
{
private:
	int angle;
	bool thrust = false;
	int lives = 3;
	int counter = 0;

public:
	//Constructors
	Ship()
	{
		angle = ANGLE_START;
		alive = true;
	}

	Ship(const Point& point) 
	{
	    angle = ANGLE_START; 
		alive = true;
	}

	//Interact
	void draw();
	int hit();
	float getAngle() const { return angle; }

	//Movement
	void moveLeft();
	void moveRight();
	void moveForward();
	void advance();
	virtual int type();

	//getters
	bool getThrust() const { return thrust; }
	int getLives() const { return lives; }
	int getCounter() const { return counter; }

	//setters
	void setThrust(bool thrust) { this->thrust = thrust; }
	void setLives(int lives) { this->lives += lives; }
	void setCounter(double counter) { this->counter += counter; }
	void resetCounter() { counter = 0; }
	void shipReborn() { alive = true; resetCounter(); }
};

#endif /* ship_h */
