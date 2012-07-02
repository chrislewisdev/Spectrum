/*****************************************************************
*Spectrum
*Player.h by Joe Park
*****************************************************************/
#ifndef Player_H
#define Player_H

#include <GameObject.h>

//Gravitational Constant
const float GRAVITY = 10.0;

class Player: public CEngine::GameObject
{
public:
	Player();
	//Note: at the moment, you aren't actually calling this from Game. If you want to call it properly you should be calling it in
	//the initialisation list for Game, e.g. Game::Game(blah, blah) : GameState(blah, blah), player(blah)
	Player(CEngine::Box2D boundingBox,float xPos,float yPos);
	~Player();

	//Move the Player according to their keypress
	void Move();

	//Draw the player according to their position
	void Draw();

	//Apply Gravity to the player
	void ApplyGravity();

	//Perform the jump action
	//No idea how to actually code this
	void Jump();

	//Check if Player's bottom side is not touching another object.
	bool CheckOnSolidGround();

private:
	float playerMoveSpeed;

	//Note: GameObject already defines a Box2D (called 'bounds') object for its positional data- this contains both a Vector2D for position and one for size.
	//You don't need a new set of x/y values here
	//This is also why your draw code doesn't work properly, because DrawBoundingBox() uses the bounds member to know where to draw
	float xPos,yPos;

	float xVel,yVel;
};

#endif