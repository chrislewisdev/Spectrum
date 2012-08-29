#include "PhysicsObject.h"
using namespace CEngine;
PhysicsObject::PhysicsObject(ColourType c)
	: ColouredObject(c)
{

}

PhysicsObject::PhysicsObject(CEngine::Box2D _boundingBox, ColourType c)
	: ColouredObject(c)
{
	bounds = _boundingBox;
	xVel = 0;
	yVel = 0;
	onSolidGround = false;
}

PhysicsObject::~PhysicsObject()
{

}

CEngine::Box2D PhysicsObject::GetBounds() const
{
	return bounds;
}

bool PhysicsObject::GetOnSolidGround() const
{
	return onSolidGround;
}

void PhysicsObject::SetOnSolidGround(bool _onSolidGround)
{
	onSolidGround = _onSolidGround;
}

void PhysicsObject::SetHittingObject(bool _hittingObject)
{
	hittingObject = _hittingObject;
}

void PhysicsObject::IncreaseYPos(float y)
{
	bounds.pos.y += y;
}

void PhysicsObject::AdjustPosition(Box2D object)
{
	if(object.pos.y > bounds.pos.y)
	{
		bounds.pos.y--;
	}
	else if(object.pos.y < bounds.pos.y)
	{
		bounds.pos.y++;
	}
}

void PhysicsObject::ApplyGravity()
{
	//Checks if the player is falling, if they are apply gravity.
	if(!onSolidGround)
	{
		bounds.pos.y += GRAVITY;
	}
}

void PhysicsObject::ObjectBelow()
{
	//Set onSolidGround to true since you have collided with an object below you.
	onSolidGround = true;

	//Set yVel to 0 so you stop falling
	yVel = 0;
}

void PhysicsObject::ObjectAbove()
{
	//Set onSolidGround to false since you cant be on solid ground if you've hit something above you.
	onSolidGround = false;

	//Set yVel to Gravity so that you begin to fall downwards.
	yVel = 0;
}

void PhysicsObject::ObjectLeft()
{
	hittingObject = true;
	bounds.pos.x -= 8.0;
}

void PhysicsObject::ObjectRight()
{
	hittingObject = true;
	bounds.pos.x += 8.0;
}

void PhysicsObject::OffsetSelf(Vector2D offset)
{
	bounds.pos += offset;
}