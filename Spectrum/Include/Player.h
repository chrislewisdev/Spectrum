/*****************************************************************
*Spectrum
*Player.h by Joe Park & Chris Lewis
*****************************************************************/
#ifndef Player_H
#define Player_H

#include "PhysicsObject.h"
#include "Box2D.h"
#include "Torch.h"

//Player Move Speed
const float playerMoveSpeed = 4.0;

class Player: public PhysicsObject
{
public:
	//Constructors
	Player();	
	Player(CEngine::Box2D _boundingBox);
	
	//Destructor
	~Player();	

	bool GetJumping() const;
	
	void ApplyGravity();
	//Move the Player according to their keypress
	void Move();

	//Draw the player according to their position
	void Draw();	

	//Perform the jump action, spends 5 frames going upwards.
	void Jump();

	//This function returns a const pointer to the player's torch
	const Torch *GetTorch() const;
	
	void ObjectAbove();
private:
	//boolean that states if the player is in the middle of a jump
	bool jumping;

	//Used to track how long the player is in a certain animation; ie jumping
	int frameCount;

	//The Player's Torch!
	Torch torch;
};

#endif