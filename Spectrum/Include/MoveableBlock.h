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

	//Inherited Function that controls what happens when the player collides with the block.
	void Collision(float playerXPos, float playerXVe);

	void ApplyGraivty();

	void Draw();
private:
	float xVel, yVel;

	bool onSolidGround;
};

#endif