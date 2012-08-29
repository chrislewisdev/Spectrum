/*****************************************************************
*Spectrum
*Player.h by Joe Park & Chris Lewis
*****************************************************************/
#ifndef Player_H
#define Player_H

#include "PhysicsObject.h"
#include "Box2D.h"
#include "Torch.h"
#include <tinyxml.h>

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

	bool GetStanding() const;

	void SetStanding(bool _standing);
	
	void ApplyGravity();

	//GameObject::Update function- Move code has been 'moved' here
	void Update(float deltaTime);

	//Draw the player according to their position
	void Draw();	

	//Perform the jump action, spends 5 frames going upwards.
	void Jump();

	//This function returns a const pointer to the player's torch
	const Torch *GetTorch() const;

	//This function updates our torch's position
	void UpdateTorch();
	
	void ObjectAbove();

	//The function that handles a collision with an object below you
	void ObjectLeft();

	//The function that handles a collision with an object above you
	void ObjectRight();

	//Function to read the player's position from Tiled XML data.
	void ReadPosition(TiXmlElement *Object);

	//This function- oddly enough- should handle collision with the player. But this will never happen!
	void PlayerCollision(PhysicsObject *target);
private:
	//boolean that states if the player is in the middle of a jump
	bool jumping;

	//Used to track how long the player is in a certain animation; ie jumping
	int frameCount;

	//The Player's Torch!
	Torch torch;

	//Extra variable to track if the player is standing on the ground but not overlapping with the ground.
	bool standing;
};

#endif