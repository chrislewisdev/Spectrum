#ifndef PhysicsObject_H
#define PhysicsObject_H

#include <GameObject.h>
#include "Box2D.h"

static const float GRAVITY = 8.0f;

class PhysicsObject : public CEngine::GameObject
{
public:
	PhysicsObject();
	PhysicsObject(CEngine::Box2D _boundingBox);
	virtual ~PhysicsObject();

	CEngine::Box2D GetBounds() const;
	bool GetOnSolidGround() const;

	void SetOnSolidGround(bool _onSolidGround);
	void SetHittingObject(bool _hittingObject);
	void IncreaseYPos(float y);

	//Apply Gravity to the object
	virtual void ApplyGravity();

	//Function that will reposition the object if it is overlapping with another object.
	virtual void AdjustPosition(CEngine::Box2D object);

	virtual void Move() = 0;

	//The function that handles a collision with an object below you
	virtual void ObjectBelow();

	//The function that handles a collision with an object above you
	virtual void ObjectAbove();

	//The function that handles a collision with an object below you
	virtual void ObjectLeft();

	//The function that handles a collision with an object above you
	virtual void ObjectRight();

protected:
	//boolean that states if the object is standing on solid ground.
	bool onSolidGround;

	//boolean used to set if an object is preventing the player from moving horizontally.
	bool hittingObject;

	//Object velocity
	float xVel,yVel;
};
#endif