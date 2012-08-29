/*****************************************************************
*Spectrum
*MovingColourBlock.h by Joe Park & Chris Lewis
*****************************************************************/

#ifndef MovingColourBlock_H
#define MovingColourBlock_H

#include "ColourBox.h"
#include "Box2D.h"
#include <Vector2D.h>
#include <vector>

const float blockMoveSpeed = 2.0;

class MovingColourBlock: public ColourBox
{
private:
	//Vector of points
	//Must be in the shape of a square/rectangle/straight line.
	std::vector<CEngine::Vector2D> path;

	//Number representing the next point along the path
	int nextPoint;	

	enum horizontalDirection {Left, Right, Not};
	enum verticalDirection {Up, Down, None};
	//Returns true for horizontal, false for vertical.
	horizontalDirection CheckHorizontalDirection();
	verticalDirection CheckVerticalDirection();

	//GameObject Update function- just calls Move()
	void Update(float deltaTime);

	bool CheckIfAtPoint();

	void LimitNextPoint();

	bool CheckIfMovementKeyIsDown();

	bool playerAttached;

	//Pointer to the object that we are carrying!
	PhysicsObject *carryTarget;

public:	

	MovingColourBlock(CEngine::Box2D boundingBox, ColourType c,
		CEngine::Vector2D pointA, CEngine::Vector2D pointB, CEngine::Vector2D pointC, CEngine::Vector2D pointD);
	//Constructor to take XML data
	MovingColourBlock(TiXmlElement *Object, ColourType c);
	
	//Inherited Function that controls what happens when the player collides with the block.
	void PlayerCollision(PhysicsObject *target);	
};

#endif