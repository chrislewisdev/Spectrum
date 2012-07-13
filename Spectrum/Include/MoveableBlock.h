/*****************************************************************
*Spectrum
*MoveableBlock.h by Joe Park
*****************************************************************/
#ifndef MoveableBlock_H
#define MoveableBlock_H

#include <GameObject.h>
#include "Box2D.h"

class MoveableBlock: public CEngine::GameObject
{
public:
	MoveableBlock(CEngine::Box2D boundingBox);

	//When the player collides push the block in that direction
	void Push(float playerXPos, float playerXVel);

	//Time for a bit of OOP
	//Precondition: player must be holding a secondard button (CRTL) to enable pull
	//No idea if we want this but i thought i most as well add it anyway.
	void Pull(float playerXPos, float playerXVel);

	void ApplyGraivty();

	void Draw();
private:
	float xVel, yVel;

	bool onSolidGround;
};

#endif