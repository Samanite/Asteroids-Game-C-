/*****************************************************
 * File: rocks.cpp
 * Author: Sam Ybarra
 *
 * Description: This file contains the method bodies
 *   for the rocks class.
 ******************************************************/

#define _USE_MATH_DEFINES
#include "rocks.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"
#include <cmath>


 /*********************************************
  * Constructor- Big Rock
  * Inherits the Rock constructor, as well sets
  * a velocity
  *********************************************/
BigRock::BigRock(const Point& point) : Rock(point)
{
	//creates a random angle
	angle = random(1, 360);
	Velocity newVelocity;

		newVelocity.setDx(ROCK_SPEED * (cos(M_PI / 180.0 * angle)));
		newVelocity.setDy(ROCK_SPEED * (sin(M_PI / 180.0 * angle)));

	setVelocity(newVelocity);
}

/*********************************************
  * Function: Big Rock draw
  * calls on draw from uiDraw.h
  *********************************************/
void BigRock::draw()
{
	bigRockSpin += BIG_ROCK_SPIN; 

	if (alive)
	{
		drawLargeAsteroid(point, bigRockSpin);
	}
}

/*********************************************
  * Function: Big Rock hit
  * kills the rock if it is hit
  *********************************************/
int BigRock::hit()
{
	kill();
	return 20;
}

/*********************************************
 * Constructor- Medium Rock
 * Inherits the Rock constructor, as well sets
 * a velocity and point
 *********************************************/
MediumRock::MediumRock(const Point& point, const Velocity & velocity, int direction) : Rock(point)
{
	
	setPoint(point);
    //Medium rock direction changes the Dy velocity
	Velocity newVelocity;
	newVelocity.setDx(velocity.getDx());
	newVelocity.setDy(velocity.getDy() + direction);
	setVelocity(newVelocity);

}

/*********************************************
  * Function: Medium Rock draw
  * calls on draw from uiDraw.h
  *********************************************/
void MediumRock::draw()
{
	if (alive)
	{
		mediumRockSpin += MEDIUM_ROCK_SPIN;

		if (alive)
		{
			drawMediumAsteroid(point, mediumRockSpin);
		}
	}
}

/*********************************************
  * Function: Medium Rock hit
  * kills the Medium Rock if it is hit
  *********************************************/
int MediumRock::hit()
{
	kill();
	return 50;
}

/*********************************************
 * Constructor- Small Rock
 * Inherits the Rock constructor, as well sets
 * a velocity
 *********************************************/
SmallRock::SmallRock(const Point& point, const Velocity& velocity, int direction) : Rock(point)
{
	
	setPoint(point);
    //Small rock direction changes the Dx velocity
	Velocity newVelocity;
	newVelocity.setDx(velocity.getDx() + direction);
	newVelocity.setDy(velocity.getDy());
	setVelocity(newVelocity);
}

/*********************************************
  * Function: Small Rock draw
  * calls on draw from uiDraw.h
  *********************************************/
void SmallRock::draw()
{
	if (alive)
	{
		smallRockSpin += SMALL_ROCK_SPIN;

		if (alive)
		{
			drawSmallAsteroid(point, smallRockSpin);
		}
	}
}

/*********************************************
  * Function: Small Rock hit
  * kills the Small Rock if it is hit
  *********************************************/
int SmallRock::hit()
{
	{
		kill();
		return 100;
	}
}


/*********************************************
  * Functions: Rock types
  * returns a number to let the program know
  * what type of  rock the vector pointer is
  * pointing to.
  *********************************************/
int BigRock::type()
{
	return 1;
}
int MediumRock::type()
{
	return 2;
}
int SmallRock::type()
{
	return 3;
}