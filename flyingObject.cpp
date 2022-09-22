/*************************************************************
 * File: flyingObject.cpp
 * Author: Sam Ybarra
 *
 * Description: Contains the method bodies for  flyingObject
 *  class.
 *************************************************************/

#include "flyingObject.h"

 /*********************************************
  * Function: advance
  * moves the point according to the velocity
  *********************************************/
void FlyingObject::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
}