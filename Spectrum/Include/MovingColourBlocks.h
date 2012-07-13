/*****************************************************************
*Spectrum
*MovingColourBlock.h by Joe Park
*****************************************************************/

#ifndef MovingColourBlock_H
#define MovingColourBlock_H

#include "ColourBox.h"
#include "Box2D.h"
#include <Vector2D.h>
#include <vector>

const float blockMoveSpeed = 4.0;

class MovingColourBlock: public ColourBox
{
private:
	//Vector of points
	//Must be in the shape of a square/rectangle/straight line.
	std::vector<CEngine::Vector2D> path;

	//Number representing the next point along the path
	int nextPoint;

	bool CheckIfAtPoint();

public:
	MovingColourBlock(CEngine::Box2D boundingBox, ColourType c,
		CEngine::Vector2D pointA, CEngine::Vector2D pointB, CEngine::Vector2D pointC, CEngine::Vector2D pointD);

	//Yes this function looks horrible :D
	//I am going to come back through and tidy it up.
	void Move();
};

#endif