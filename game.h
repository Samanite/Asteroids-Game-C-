/*************************************************************
 * File: game.h
 * Author: Sam Ybarra
 *
 * Description: The game of Asteroids. This class holds each piece
 *  of the game (rocks, bullets, ship, score). It also has
 *  methods that make the game happen (advance, interact, etc.)
 *************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "ship.h"
#include "bullet.h"
#include "rocks.h"

//create the game
#define BIG_ROCK_CLOSE_ENOUGH 17
#define MEDIUM_ROCK_CLOSE_ENOUGH 9
#define SMALL_ROCK_CLOSE_ENOUGH 5 //Adjusted to help with collisions

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
	/*********************************************
	 * Constructor
	 * Initializes the game
	 *********************************************/
	Game(Point tl, Point br);
	~Game();

	/*********************************************
	 * Function: handleInput
	 * Description: Takes actions according to whatever
	 *  keys the user has pressed.
	 *********************************************/
	void handleInput(const Interface& ui);

	/*********************************************
	 * Function: advance
	 * Description: Move everything forward one
	 *  step in time.
	 *********************************************/
	void advance();

	/*********************************************
	 * Function: draw
	 * Description: draws everything for the game.
	 *********************************************/
	void draw(const Interface& ui);

	float getClosestDistance(const FlyingObject& obj1, const FlyingObject& obj2) const;

private:
	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;
	int startGame = 0;

	//ship and score
	int score;
	Ship ship;

	//Bullet vectors
	std::vector<Bullet> bullets;
	std::vector<int> bLife;

	// Rocks vector 
	std::vector<Rock*> rocks; 

	/*************************************************
	 * Private methods to help with the game logic.
	 *************************************************/
	bool isOnScreen(const Point& point);
	void advanceBullets();
	void advanceRock();
	void advanceShip();
	void createRock();
	void createMediumRock(const Point & point, const Velocity & velocity, int direction);
	void createSmallRock(const Point& point, const Velocity& velocity, int direction);

	void handleCollisions();
	void cleanUpZombies();
};

#endif /* GAME_H */
