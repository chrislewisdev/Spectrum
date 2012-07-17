#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{

}

PhysicsObject::PhysicsObject(CEngine::Box2D _boundingBox)
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

void PhysicsObject::SetOnSolidGround(bool _onSolidGround)
{
	onSolidGround = _onSolidGround;
}

void PhysicsObject::SetXVel(float _xVel)
{
	xVel = _xVel;
}

void PhysicsObject::SetYVel(float _yVel)
{
	yVel = _yVel;
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
	yVel += GRAVITY;
}
