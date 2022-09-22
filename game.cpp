/*************************************************************
 * File: game.cpp
 * Author: Sam Ybarra
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>


#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "rocks.h"
#include <vector>
#include "ship.h"

using namespace std;
#define OFF_SCREEN_BORDER_AMOUNT 5

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObject &obj1,const FlyingObject & obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br), ship()
{
	// Set up the initial conditions of the game
	score = 0;
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
	//Check for dead rocks
	vector<Rock*>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		//set a pointer to hold the value
		Rock* pRock = *rockIt;
		if (!pRock->isAlive())
		{
			// Delete the pointer memory
			delete pRock;

			// remove from list and advance
			rockIt = rocks.erase(rockIt);
			pRock = NULL;
		}
	}
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game::advance()
{
	advanceBullets();
	advanceRock();
	advanceShip();

	handleCollisions();
	cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE SHIP
 * Advance the ship if it is alive.
 ***************************************/
void Game::advanceShip()
{
	if (ship.isAlive())
	{
		ship.advance();
	}
	
	    //wrap if needed
		if (!isOnScreen(ship.getPoint()))
		{
			Point tempPoint;
			tempPoint = ship.getPoint();

			//If exiting side of screen
			//change the x coordinate
			if (tempPoint.getX() >= 195)
			{
				tempPoint.setX(194 * -1);
				ship.setPoint(tempPoint);
			}
			if (tempPoint.getX() <= -195)
			{
				tempPoint.setX(-194 * -1);
				ship.setPoint(tempPoint);
			}
			//If exiting top/bottom of screen
			//change the y coordinate
			if (tempPoint.getY() >= 195)
			{
				tempPoint.setY(194 * -1);
				ship.setPoint(tempPoint);
			}
			if (tempPoint.getY() <= -195)
			{
				tempPoint.setY(-194 * -1);
				ship.setPoint(tempPoint);
			}

		}
	
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		//counter for life of bullet
		bLife[i] += 1;
		//Kill if bullet is too old
		if (bLife[i] >= 40)
		{
			bullets[i].kill();
		}
		if (bullets[i].isAlive())
		{
			// Bullet is alive, move forward
			bullets[i].advance();
		}

		//wrap if needed
		if (!isOnScreen(bullets[i].getPoint()))
		{
			Point tempPoint;
			tempPoint = bullets[i].getPoint();

			//If exiting side of screen
			//change the x coordinate
			if (tempPoint.getX() >= 195)
			{
				tempPoint.setX(194 * -1);
				bullets[i].setPoint(tempPoint);
			}
			if (tempPoint.getX() <= -195)
			{
				tempPoint.setX(-194 * -1);
				bullets[i].setPoint(tempPoint);
			}
			//If exiting top/bottom of screen
			//change the y coordinate
			if (tempPoint.getY() >= 195)
			{
				tempPoint.setY(194 * -1);
				bullets[i].setPoint(tempPoint);
			}
			if (tempPoint.getY() <= -195)
			{
				tempPoint.setY(-194 * -1);
				bullets[i].setPoint(tempPoint);
			}

		}
	}
}

/**************************************************************************
 * GAME :: ADVANCE ROCK
 *
 * 1. If there is no rock, create one with some probability
 * 2. If there is a rock, and it's alive, advance it
 * 3. Check if the rock has gone of the screen, and if so, "kill" it
 **************************************************************************/
void Game::advanceRock()
{
	if (rocks.size() == 0)
	{
		// there are no rocks right now

		for (int i =0; i < 5; i++)
		{
			// create a new set of rocks
			createRock();
		}
	}
	else
	{
		for (int i = 0; i < rocks.size(); i++)
		{
			if (rocks[i]->isAlive())
			{
				rocks[i]->advance();
			}

			//wrap if needed
			if (!isOnScreen(rocks[i]->getPoint()))
			{
				Point tempPoint;
				tempPoint = rocks[i]->getPoint();
				
				//If exiting side of screen
			    //change the x coordinate
				if (tempPoint.getX() >= 195)
				{
					tempPoint.setX(194 * -1);
					rocks[i]->setPoint(tempPoint);
				}
				if (tempPoint.getX() <= -195)
				{
					tempPoint.setX(-194 * -1);
					rocks[i]->setPoint(tempPoint);
				}
				//If exiting top/bottom of screen
			    //change the y coordinate
				if (tempPoint.getY() >= 195) 
				{
						tempPoint.setY(194 * -1);
						rocks[i]->setPoint(tempPoint);
				}
				if (tempPoint.getY() <= -195)
				{
					tempPoint.setY(-194 * -1);
					rocks[i]->setPoint(tempPoint);
				}
				
			}
		}
	}

}

/**************************************************************************
 * GAME :: CREATE ROCK
 * Create a rock of a big type according to the rules of the game.
 **************************************************************************/
void Game::createRock()
{
	Rock* newBigRock = NULL;

	// For big rock type
	Point newPoint;
	newPoint.setX(random(topLeft.getX(), bottomRight.getX())); 
	newPoint.setY(random(bottomRight.getY(), topLeft.getY()));

		newBigRock = new BigRock(newPoint);
		rocks.push_back(newBigRock);

}

/**************************************************************************
 * GAME :: CREATE MEDIUM ROCK
 * Create a rock of a medium type according to the rules of the game.
 **************************************************************************/
void Game::createMediumRock(const Point& point, const Velocity& velocity, int direction)
{
	Rock* newMedRock = NULL;

	newMedRock = new MediumRock(point, velocity, direction);
	rocks.push_back(newMedRock);

}

/**************************************************************************
 * GAME :: CREATE SMALL ROCK
 * Create a rock of a small type according to the rules of the game.
 **************************************************************************/
void Game::createSmallRock(const Point& point, const Velocity& velocity, int direction)
{
	Rock* newSmallRock = NULL;

	newSmallRock = new SmallRock(point, velocity, direction);
	rocks.push_back(newSmallRock);
}

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game::isOnScreen(const Point& point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a rock and a bullet, or ship and rock.
 **************************************************************************/
void Game::handleCollisions()
{ 
	bool hitBig = false;
	bool hitMedium = false;
	Velocity velocityRock;
	Point pointRock;
	// now check for a hit (if it is close enough to any live bullets)
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < rocks.size(); j++)
		{

			//Rock* pRock = *it;

			if (bullets[i].isAlive())
			{
				// this bullet is alive, see if its too close

				// check if the rock is at this point (in case it was hit)
				if (rocks[j]->isAlive())
				{

                    if (rocks[j]->type() == 3)
					{
						if (getClosestDistance(bullets[i], *rocks[j]) <= SMALL_ROCK_CLOSE_ENOUGH)
						{
							// hit the rock
							int points = rocks[j]->hit();
							score += points;
							// the bullet is dead as well
							bullets[i].kill();
						}
						else if (getClosestDistance(bullets[i], *rocks[j]) < 0)
						{
							if (getClosestDistance(bullets[i], *rocks[j]) >= SMALL_ROCK_CLOSE_ENOUGH)
							{
								// hit the rock
								int points = rocks[j]->hit();
								score += points;
								// the bullet is dead as well
								bullets[i].kill();
							}
						}
					}
                    else if (rocks[j]->type() == 2)
					{
						if (getClosestDistance(bullets[i], *rocks[j]) <= MEDIUM_ROCK_CLOSE_ENOUGH) 
						{
							velocityRock = rocks[j]->getVelocity();
							pointRock = rocks[j]->getPoint();
							hitMedium = true;
							// hit the rock
							int points = rocks[j]->hit();
							score += points;
							// the bullet is dead as well
							bullets[i].kill();
						}
						else if (getClosestDistance(bullets[i], *rocks[j]) < 0)
						{
							if (getClosestDistance(bullets[i], *rocks[j]) >= MEDIUM_ROCK_CLOSE_ENOUGH)
							{
								// hit the rock
								int points = rocks[j]->hit();
								score += points;
								// the bullet is dead as well
								bullets[i].kill();
							}
						}
					}

					else if (rocks[j]->type() == 1)
					{
						if (getClosestDistance(bullets[i], *rocks[j]) <= BIG_ROCK_CLOSE_ENOUGH) 
						{
							velocityRock = rocks[j]->getVelocity();
							pointRock = rocks[j]->getPoint();
							// hit the rock
							hitBig = true;
							int points = rocks[j]->hit();
							score += points;
							// the bullet is dead as well
							bullets[i].kill();
							
						}
						else if (getClosestDistance(bullets[i], *rocks[j]) < 0)
						{
							if (getClosestDistance(bullets[i], *rocks[j]) >= BIG_ROCK_CLOSE_ENOUGH)
							{
								// hit the rock
								int points = rocks[j]->hit();
								score += points;
								// the bullet is dead as well
								bullets[i].kill();
							}
						}
					}
					
					
				}
			} // if bullet is alive
		}

	} // for bullets  
	
	for (int i = 0; i < rocks.size(); i++)
	{
		//Rock* pRock = *it;
		if (ship.isAlive())
		{
           if (rocks[i]->type() == 3)
			{
				if (getClosestDistance(ship, *rocks[i]) <= SMALL_ROCK_CLOSE_ENOUGH)
				{
					int points = rocks[i]->hit();
					score += points;
					ship.kill();
					ship.setLives(-1);
				}
				else if (getClosestDistance(ship, *rocks[i]) < 0)
				{
					if (getClosestDistance(ship, *rocks[i]) >= SMALL_ROCK_CLOSE_ENOUGH)
					{
						int points = rocks[i]->hit();
						score += points;
						ship.kill();
						ship.setLives(-1);
					}
				}
			}

            else if (rocks[i]->type() == 2)
			{
				if (getClosestDistance(ship, *rocks[i]) <= MEDIUM_ROCK_CLOSE_ENOUGH)
				{
					velocityRock = rocks[i]->getVelocity();
					pointRock = rocks[i]->getPoint();
					hitMedium = true;
					int points = rocks[i]->hit();
					score += points;
					ship.kill();
					ship.setLives(-1);
				}
				else if (getClosestDistance(ship, *rocks[i]) < 0)
				{
					if (getClosestDistance(ship, *rocks[i]) >= MEDIUM_ROCK_CLOSE_ENOUGH)
					{
						int points = rocks[i]->hit();
						score += points;
						ship.kill();
						ship.setLives(-1);
					}
				}
			}
			else if (rocks[i]->type() == 1)
			{
				if (getClosestDistance(ship, *rocks[i]) <= BIG_ROCK_CLOSE_ENOUGH)
				{
					velocityRock = rocks[i]->getVelocity();
					pointRock = rocks[i]->getPoint();
					// hit the rock
					hitBig = true;
					int points = rocks[i]->hit();
					score += points;
					ship.kill();
					ship.setLives(-1);
				}
				else if (getClosestDistance(ship, *rocks[i]) < 0)
				{
					if (getClosestDistance(ship, *rocks[i]) >= BIG_ROCK_CLOSE_ENOUGH)
					{
						int points = rocks[i]->hit();
						score += points;
						ship.kill();
						ship.setLives(-1);
					}
				}
			}
			
			
		}
	} 

if (hitBig)
	{
		createMediumRock(pointRock, velocityRock, 1);
		createMediumRock(pointRock, velocityRock, -1);
		createSmallRock(pointRock, velocityRock, 2);
	}
	else if (hitMedium)
	{
		createSmallRock(pointRock, velocityRock, 3);
		createSmallRock(pointRock, velocityRock, -3);
	}

} 

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game::cleanUpZombies()
{
	// check for dead rock
	vector<Rock*>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		Rock* pRock = *rockIt;
		if (!pRock->isAlive()) 
		{
			// Delete pointer memory
			delete pRock;

			// remove from list and advance
			rockIt = rocks.erase(rockIt);
			pRock = NULL;
		}
		else
		{
			rockIt++; // advance
		}
	}

	// Look for dead bullets & also delete bullet life vector
	
	//Run through both vectors at the same time
	vector<Bullet>::iterator bulletIt = bullets.begin();
	vector<int>::iterator bLifeIt = bLife.begin();

	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		int BL = *bLifeIt;

		if (!bullet.isAlive())
		{
			// remove both from list and advance
			bulletIt = bullets.erase(bulletIt);
			bLifeIt = bLife.erase(bLifeIt);
		}
		else
		{
			bulletIt++; // advance both
			bLifeIt++;
		}
	}
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game::handleInput(const Interface& ui)
{
	ship.setThrust(false);
	// Change the direction of the ship
	if (ui.isLeft())
	{
		ship.moveLeft();
	}

	if (ui.isRight())
	{
		ship.moveRight();
	}

	if (ui.isUp())
	{
		ship.moveForward();
		ship.setThrust(true);
	}

	// Check for "Spacebar
	if (ui.isSpace()&& ship.isAlive())
	{
		//Create both a bullet and a counter
		Bullet newBullet;
		int newBlife = 0;

		//Pass ship point, angle, and velocity to bullet
		newBullet.fire(ship.getPoint(), ship.getAngle(), ship.getVelocity());

		bullets.push_back(newBullet);
		bLife.push_back(newBlife);
	}
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game::draw(const Interface& ui)
{
	//Start with the title screen
	if (startGame < 100)
	{
			Point introTextLocation;
			introTextLocation.setX(-35);
			char introText[] = "ASTEROIDS";
			drawText(introTextLocation, introText);
			Point shipPoint;
			shipPoint.setY(-10);
			shipPoint.setX(-80 + startGame*3);
			drawShip(shipPoint, 270, true);
			startGame++;
		
	}
	else
	{
		// draw the rock
		for (int i = 0; i < rocks.size(); i++)
		{
			if (rocks[i]->isAlive())
			{
				rocks[i]->draw();
			}
		}
		if (ship.isAlive())
		{
			// draw the ship
			ship.draw();
		}
		if (!(ship.isAlive()) && ship.getLives() > 0)
		{
			if (ship.getCounter() >= 50)
			{
				Point newPoint;
				Velocity newVelocity;
				ship.setPoint(newPoint);
				ship.setVelocity(newVelocity);
				ship.shipReborn();
			}
			else
			{
				ship.setCounter(1);
			}
		}
		if (ship.getLives() == 0)
		{
			Point exitTextLocation;
			exitTextLocation.setX(-35);
			char exitText[] = "GAME OVER";
			drawText(exitTextLocation, exitText);
		}
		// draw the bullets, if they are alive
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())
			{
				bullets[i].draw();
			}
		}

		//TODO: Put the score on the screen
		Point scoreTextLocation;
		scoreTextLocation.setX(topLeft.getX() + 5);
		scoreTextLocation.setY(topLeft.getY() - 15);
		char textScore[] = "SCORE: ";
		drawText(scoreTextLocation, textScore);

		Point scoreLocation;
		scoreLocation.setX(topLeft.getX() + 55);
		scoreLocation.setY(topLeft.getY() - 5);
		drawNumber(scoreLocation, score);

		Point lifeTextLocation;
		lifeTextLocation.setX(topLeft.getX() + 5);
		lifeTextLocation.setY(topLeft.getY() - 30);
		char textLives[] = "LIVES: ";
		drawText(lifeTextLocation, textLives);

		Point lifeLocation;
		lifeLocation.setX(topLeft.getX() + 55);
		lifeLocation.setY(topLeft.getY() - 20);
		drawNumber(lifeLocation, ship.getLives());
	}
}
