/*****************************************************************
*Spectrum
*MovingColourBlock.cpp by Joe Park & Chris Lewis
*****************************************************************/
#include "MovingColourBlocks.h"
#include <ProgramControl.h>
#include <assert.h>
#include <string>

using namespace std;
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

MovingColourBlock::MovingColourBlock(TiXmlElement *Object, ColourType c)
	: ColourBox(Object, c)
{
	path.resize(4);

	TiXmlElement *Property = Object->FirstChildElement("properties")->FirstChildElement("property");

	while (Property)
	{
		string name(Property->Attribute("name"));
		int tempValue;

		Property->QueryIntAttribute("value", &tempValue);

		if (name == "x1") path[0].x = (float)tempValue;
		else if (name == "x2") path[1].x = (float)tempValue;
		else if (name == "x3") path[2].x = (float)tempValue;
		else if (name == "x4") path[3].x = (float)tempValue;
		else if (name == "y1") path[0].y = (float)tempValue;
		else if (name == "y2") path[1].y = (float)tempValue;
		else if (name == "y3") path[2].y = (float)tempValue;
		else if (name == "y4") path[3].y = (float)tempValue;

		Property = Property->NextSiblingElement();
	}

	bounds.pos = path[0];
	nextPoint = 1;
}

MovingColourBlock::horizontalDirection MovingColourBlock::CheckHorizontalDirection()
{
	if(path[nextPoint-1].x < path[nextPoint].x)
	{
		return MovingColourBlock::Right;
	}
	else if(path[nextPoint-1].x > path[nextPoint].x)
	{
		return MovingColourBlock::Left;
	}
	else
		return MovingColourBlock::Not;
}

MovingColourBlock::verticalDirection MovingColourBlock::CheckVerticalDirection()
{
	if(path[nextPoint-1].y < path[nextPoint].y)
	{
		return MovingColourBlock::Down;
	}
	else if(path[nextPoint-1].y > path[nextPoint].y)
	{
		return MovingColourBlock::Up;
	}
	else
		return MovingColourBlock::None;
}

//This function performs our GameObject Update, so it'll work when used in generic GameStorage
void MovingColourBlock::Update(float deltaTime)
{
	Move();
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

bool MovingColourBlock::CheckIfMovementKeyIsDown()
{
	if (ProgramControl::ProgramInput.GetKey('w'))
		return true;
	if (ProgramControl::ProgramInput.GetKey('a'))
		return true;
	if (ProgramControl::ProgramInput.GetKey('d'))
		return true;
}

void MovingColourBlock::Collision(CEngine::Box2D target)
{
	if(playerAttached)
	{
		if(CheckIfMovementKeyIsDown())
		{
			playerAttached = false;
		}
		else
		{	
			playerAttached = true;

			if(CheckHorizontalDirection() == MovingColourBlock::Left)
			{
				target.pos.x -= 4.0;
			}
			else if(CheckHorizontalDirection() == MovingColourBlock::Right)
			{
				target.pos.x -= 4.0;
			}

			if(CheckVerticalDirection() == 	MovingColourBlock::Up)
			{
				target.pos.y -= 4.0;
			}
			else if(CheckVerticalDirection() == MovingColourBlock::Down)
			{
				target.pos.y += 4.0;
			}
		}
	}
}