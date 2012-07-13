/*****************************************************************
*Spectrum
*Player.h by Joe Park
*****************************************************************/
#ifndef Player_H
#define Player_H

#include <GameObject.h>
#include "Box2D.h"
#include "Torch.h"

//Gravitational Constant
const float GRAVITY = 8.0;

//Player Move Speed
const float playerMoveSpeed = 4.0;

class Player: public CEngine::GameObject
{
public:
	//Constructors
	Player();	
	Player(CEngine::Box2D _boundingBox);
	
	//Destructor
	~Player();

	//Returns the bounding box around the player
	CEngine::Box2D GetBounds() const;

	//Set methods
	void setOnSolidGround(bool _onSolidGround);
	void setJumping(bool _jumping);
	void setyVel(float _yVel);

	//Move the Player according to their keypress
	void Move();

	//Draw the player according to their position
	void Draw();

	//Apply Gravity to the player
	void ApplyGravity();

	//Perform the jump action, spends 5 frames going upwards.
	void Jump();

	//The function that handles a collesion with an object below you
	void ObjectBelow();

	//The function that handles a collesion with an object above you
	void ObjectAbove();

private:
	//boolean that states if the player is standing on solid ground.
	bool onSolidGround;

	//boolean that states if the player is in the middle of a jump
	bool jumping;

	//Used to track how long the player is in a certain animation; ie jumping
	int frameCount;
	
	//Players velocity
	float xVel,yVel;

	//The Player's Torch!
	Torch torch;
};

#endif