/***********************************************************************
 * Header File:
 *    Bullet : A type of flying object
 * Author:
 *    Sam Ybarra
 * Summary:
 *    A bullet has a point, velocity, and radius. Fire initiates its
 *    movement and it interacts with other flying objects through the
 *    kill function.
 ************************************************************************/

#ifndef BULLET_H
#define BULLET_H

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"
#include <cmath>

#define BULLET_SPEED 5.0

 /*********************************************
  * BULLET
  * A flying object (life, velocity, point) and
  * in addition needs to be fired
  *********************************************/
class Bullet : public FlyingObject
{
private:
	float angle = 60.0;

public:
	//Constructors
	Bullet()
	{
		alive = true;
	}
	//~Bullet(){}

	//Interact
	void advance();
	void draw();
	void fire(const Point& point, float angle, const Velocity& velocityShip);
	virtual int type();

};

#endif //BULLET_H
