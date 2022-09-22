/***********************************************************************
 * Header File:
 *    Flying Object : The base class of all flying objects.
 * Author:
 *    Sam Ybarra
 * Summary:
 *    Includes a point, velocity, and alive or not bool.
 ************************************************************************/

#ifndef FLYING_OBJECT_H
#define FLYING_OBJECT_H

#include "point.h"
#include "velocity.h"
#include <cmath>

 /*********************************************
  * FLYING_OBJECT
  * An object with a life, velocity, and point
  *********************************************/
class FlyingObject
{
protected:
	Point point;
	bool alive = true;
	Velocity velocity;

public:
	//Constructors
	FlyingObject()
	{
		point.setX(0.0);
		point.setY(0.0);
		alive = true;
		velocity.setDx(0.0);
		velocity.setDy(0.0);

	}

	//Getters
	Point getPoint() const { return point; }
	Velocity getVelocity() const { return velocity; }

	//Setters
	void setPoint(const Point& point) { this->point = point; }
	void setVelocity(const Velocity& velocity) { this->velocity = velocity; }
	void setAlive(bool alive) { this->alive = alive; }

	//Life of object
	bool isAlive() const { return alive; }
	void kill() { alive = false; }

	//Interact
	virtual void advance();
	virtual void draw() = 0;
	virtual int type() = 0;

};

#endif //FLYING_OBJECT_H
