/*****************************************************************
*Spectrum
*MoveableBlock.h by Joe Park
*****************************************************************/
#ifndef MoveableBlock_H
#define MoveableBlock_H

#include "PhysicsObject.h"
#include "Box2D.h"

class MoveableBlock : public PhysicsObject
{
public:
	MoveableBlock(CEngine::Box2D boundingBox);

	//Inherited Function that controls what happens when the player collides with the block.
	void Collision(float playerXPos, float playerXVe);

	void ApplyGraivty();

	void Draw();

	//Player Collision function inherited off of PhysicsObject
	void PlayerCollision(PhysicsObject *target);
private:
	float xVel, yVel;

	bool onSolidGround;
};

#endif