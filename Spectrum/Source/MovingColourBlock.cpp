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
	path[0] = pointA;
	path[1] = pointB;
	path[2] = pointC;
	path[3] = pointD;

	//Set starting position
	bounds.pos.x = pointA.x;
	bounds.pos.y = pointA.y;

	//Set next point to 1
	nextPoint = 1;
}

void MovingColourBlock::Move()
{
	//Check if during the last update the box reached a point.
	LimitNextPoint();

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
			if(CheckIfAtPoint())
				nextPoint++;
			LimitNextPoint();
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
			if(CheckIfAtPoint())
				nextPoint++;
			LimitNextPoint();
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
			if(CheckIfAtPoint())
				nextPoint++;
			LimitNextPoint();
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
			if(CheckIfAtPoint())
				nextPoint++;
			LimitNextPoint();
		}
	}
	else
	{
		nextPoint++;
		LimitNextPoint();
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

void MovingColourBlock::LimitNextPoint()
{
	if(nextPoint > path.size()-1)
	{
		nextPoint = 0;
	}
}