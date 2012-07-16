/*****************************************************************
*Spectrum
*MovingColourBlock.cpp by Joe Park
*****************************************************************/
#include "MovingColourBlocks.h"
#include <assert.h>
using namespace CEngine;
MovingColourBlock::MovingColourBlock(CEngine::Box2D boundingBox, ColourType c,
	Vector2D pointA, Vector2D pointB, Vector2D pointC, Vector2D pointD)
	: ColourBox(boundingBox, c)
{
	
	path.resize(4);

	//Add path points
	path.push_back(pointA);
	path.push_back(pointB);
	path.push_back(pointC);
	path.push_back(pointD);

	//Set starting position
	bounds.pos.x = pointA.x;
	bounds.pos.y = pointA.y;

	//Set next point to 1
	nextPoint = 1;
}

void MovingColourBlock::Move()
{
	//Check if during the last update the box reached a point.

	if(!CheckIfAtPoint())
	{
		if		(path[nextPoint].x >= bounds.pos.x && path[nextPoint].y >= bounds.pos.y)
		{
			if(path[nextPoint].x == bounds.pos.x)
				bounds.pos.y += blockMoveSpeed;
			else if(path[nextPoint].y == bounds.pos.y)
				bounds.pos.x += blockMoveSpeed;
			else
			{
				bounds.pos.x += blockMoveSpeed;
				bounds.pos.y += blockMoveSpeed;
			}
		}
		else if(path[nextPoint].x >= bounds.pos.x && path[nextPoint].y <= bounds.pos.y)
		{
			if(path[nextPoint].x == bounds.pos.x)
				bounds.pos.y -= blockMoveSpeed;
			else if(path[nextPoint].y == bounds.pos.y)
				bounds.pos.x += blockMoveSpeed;
			else
			{
				bounds.pos.x += blockMoveSpeed;
				bounds.pos.y -= blockMoveSpeed;
			}
		}
		else if(path[nextPoint].x <= bounds.pos.x && path[nextPoint].y >= bounds.pos.y)
		{
			if(path[nextPoint].x == bounds.pos.x)
				bounds.pos.y += blockMoveSpeed;
			else if(path[nextPoint].y == bounds.pos.y)
				bounds.pos.x -= blockMoveSpeed;
			else
			{
				bounds.pos.x -= blockMoveSpeed;
				bounds.pos.y += blockMoveSpeed;
			}
		}
		else if(path[nextPoint].x <= bounds.pos.x && path[nextPoint].y <= bounds.pos.y)
		{
			if(path[nextPoint].x == bounds.pos.x)
				bounds.pos.y -= blockMoveSpeed;
			else if(path[nextPoint].y == bounds.pos.y)
				bounds.pos.x -= blockMoveSpeed;
			else
			{
				bounds.pos.x -= blockMoveSpeed;
				bounds.pos.y -= blockMoveSpeed;
			}
		}
	}
	else
	{
		nextPoint++;
		if(nextPoint > 4)
		{
			//Loop completed returned to origin
			nextPoint = 0;
		}
	}
}

bool MovingColourBlock::CheckIfAtPoint()
{
	if(bounds.pos.x == path[nextPoint].x && bounds.pos.y == path[nextPoint].y)
	{
		return true;
	}
	else
	{
		return false;
	}
}