/***********************************************************************
 * Header File:
 *    Velocity : Creates a x y movement across the screen.
 * Author:
 *    Sam Ybarra
 * Summary:
 *    This stores the speed and direction with x and y
 *    coordinates.
 ************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

#include "point.h" 

 /*********************************************
  * VELOCITY
  * Holds inertia with x and y coordinates
  *********************************************/
class Velocity
{
private:
	float Dx = 0.0;
	float Dy = 0.0;
public:
	//Constructors
	Velocity()
	{
		Dx = 0.0;
		Dy = 0.0;
	}

	Velocity(float x, float y)
	{
		Dx = x;
		Dy = y;
	}

	//Getters
	float getDx() const { return Dx; }
	float getDy() const { return Dy; }

	//Setters
	void setDx(float x) { Dx += x; }
	void setDy(float y) { Dy += y; }

};

#endif //VELOCITY_H