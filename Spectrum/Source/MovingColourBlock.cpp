/*****************************************************************
*Spectrum
*MovingColourBlock.cpp by Joe Park & Chris Lewis
*****************************************************************/
#include "MovingColourBlocks.h"
#include <ProgramControl.h>
#include <assert.h>
#include <string>
#include <CEMath.h>

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

	playerAttached = false;
	carryTarget = NULL;
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

	playerAttached = false;
	carryTarget = NULL;
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
	//Check if during the last update the box reached a point.
	LimitNextPoint();

	Vector2D direction = path[nextPoint] - bounds.pos;

	if (direction.Length() > 2)
	{
		bounds.pos += direction.UnitVector();

		//If we're carrying anyone, move them as well
		if (playerAttached)
		{
			//Check they're still above us!
			Box2D collisionArea = bounds;
			collisionArea.pos.y -= 2;
			if (!collisionArea.Overlap(carryTarget->BoundingBox())) 
			{
				playerAttached = false;
				carryTarget = NULL;
			}
			else
			{
				carryTarget->OffsetSelf(direction.UnitVector());
			}
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
	/*if (ProgramControl::ProgramInput.GetKey('a'))
		return true;
	if (ProgramControl::ProgramInput.GetKey('d'))
		return true;*/
	else
		return false;
}

void MovingColourBlock::PlayerCollision(PhysicsObject *target)
{
	//Grab the angle to our target (used to determine if the object is above or not)
	float angle = Math::Angle(bounds.pos + bounds.size/2, target->BoundingBox().pos + target->BoundingBox().size/2);
	Box2D collisionArea = bounds;
	collisionArea.pos.y -= 2;

	if (collisionArea.Overlap(target->BoundingBox()) && (CurrentColour() == Colour() || Colour() == COLOUR_WHITE))
	{
		if(CheckIfMovementKeyIsDown())
		{
			playerAttached = false;
			carryTarget = NULL;
		}
		else if (angle > -135 && angle < -45)
		{	
			playerAttached = true;
			carryTarget = target;

			/*if(CheckHorizontalDirection() == MovingColourBlock::Left)
			{
				target->OffsetSelf(Vector2D(-4, 0));
			}
			else if(CheckHorizontalDirection() == MovingColourBlock::Right)
			{
				target->OffsetSelf(Vector2D(4, 0));
			}

			if(CheckVerticalDirection() == 	MovingColourBlock::Up)
			{
				target->OffsetSelf(Vector2D(0, -4));
			}
			else if(CheckVerticalDirection() == MovingColourBlock::Down)
			{
				target->OffsetSelf(Vector2D(0, 4));
			}*/
		}
	}
}