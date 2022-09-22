/*****************************************************
 * File: ship.cpp
 * Author: Sam Ybarra
 *
 * Description: This file contains the method bodies
 *   for the ship class.
 ******************************************************/

#define _USE_MATH_DEFINES
#include "ship.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"
#include <cmath>
// Put your ship methods here
/*********************************************
  * Function: Ship draw
  * calls on draw from uiDraw.h
  *********************************************/
void Ship::draw()
{
	if (alive)
	{
		//draw ship
		drawShip(point, angle-90, thrust);
	}
}

/*********************************************
 * Function: advance
 * calls on the flying object advance method
 *********************************************/
void Ship::advance()
{
	FlyingObject::advance();
}

/*********************************************
  * Function: Move Left
  * calls on draw from uiDraw.h
  *********************************************/
void Ship::moveLeft()
{
	angle += ROTATE_AMOUNT;
	if (angle > 360)
	{
		int tempAngle = angle;
		angle = (tempAngle - 360);
	}
}

/*********************************************
  * Function: Move Right
  * calls on draw from uiDraw.h
  *********************************************/
void Ship::moveRight()
{
	angle -= ROTATE_AMOUNT;
	if (angle < 0)
	{
		int tempAngle = angle;
		angle = (tempAngle + 360);
	}
}

/*********************************************
  * Function: Move Forward
  * calls on draw from uiDraw.h
  *********************************************/
void Ship::moveForward()
{
	//TODO: Find a way to set thurst to true when pressed

	Velocity newVelocity;
	newVelocity.setDx(THRUST_AMOUNT* (cos(M_PI / 180.0 * angle)));
	newVelocity.setDy(THRUST_AMOUNT * (sin(M_PI / 180.0 * angle)));
	
	velocity.setDx(newVelocity.getDx());
	velocity.setDy(newVelocity.getDy());
}
/*********************************************
  * Function: Ship hit
  * kills the ship if it is hit
  *********************************************/
int Ship::hit()
{
	kill();
	return 0;
}

/*********************************************
  * Function: Ship type
  * Function not needed.
  *********************************************/
int Ship::type()
{
	return 0;
}