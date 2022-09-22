/*****************************************************
 * File: bullet.cpp
 * Author: Sam Ybarra
 *
 * Description: This file contains the method bodies
 *   for the bullet class.
 ******************************************************/

#define _USE_MATH_DEFINES
#include <cmath>
#include "bullet.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"

using namespace std;

/*********************************************
 * Function: advance
 * calls on the flying object advance method
 *********************************************/
void Bullet::advance()
{
	FlyingObject::advance();
}

/*********************************************
* Function: draw
* calls on drawDot from uiDraw
*********************************************/
void Bullet::draw()
{
	if (alive)
	{
		drawDot(getPoint());
	}
}

/*********************************************
* Function: fire
* starts the movement of the bullet
*********************************************/
void Bullet::fire(const Point& point, float angle, const Velocity& velocityShip)
{
	if (angle > 360)
	{
		int tempAngle = angle;
		angle = (tempAngle - 360);
	}
	if (angle < 0)
	{
		int tempAngle = angle;
		angle = (tempAngle + 360);
	}
	//set the starting point
	this->point = point;
	//set the bullet velocity and angle, add ship velocity
	velocity.setDx((BULLET_SPEED * (cos(M_PI / 180.0 * angle))) + velocityShip.getDx());
	velocity.setDy((BULLET_SPEED * (sin(M_PI / 180.0 * angle))) + velocityShip.getDy());

	alive = true;
}

int Bullet::type()
{
	return 0;
}