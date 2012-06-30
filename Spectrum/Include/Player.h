/*****************************************************************
*Spectrum
*Player.h by Joe Park
*****************************************************************/
#ifndef Player_H
#define Player_H

#include <GameObject.h>
#include "Main.h"

//Gravitational Constant
const float GRAVITY = 10.0;

class Player: public CEngine::GameObject
{
public:
	Player();
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
	float xPos,yPos;
	float xVel,yVel;
};

#endif