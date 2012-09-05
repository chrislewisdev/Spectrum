#ifndef PhysicsObject_H
#define PhysicsObject_H

#include "ColouredObject.h"
#include "Box2D.h"

static const float GRAVITY = 8.0f;

class PhysicsObject : public ColouredObject
{
public:
	PhysicsObject(ColourType c);
	PhysicsObject(CEngine::Box2D _boundingBox, ColourType c);
	virtual ~PhysicsObject();

	CEngine::Box2D GetBounds() const;
	bool GetOnSolidGround() const;
	bool IsMoveable() const;

	void SetOnSolidGround(bool _onSolidGround);
	void SetHittingObject(bool _hittingObject);

	//Apply Gravity to the object
	virtual void ApplyGravity();

	//Function that will reposition the object if it is overlapping with another object.
	virtual void AdjustPosition(CEngine::Box2D object);

	//The function that handles a collision with an object below you
	virtual void ObjectBelow();

	//The function that handles a collision with an object above you
	virtual void ObjectAbove();

	//The function that handles a collision with an object below you
	virtual void ObjectLeft();

	//The function that handles a collision with an object above you
	virtual void ObjectRight();

	//Virtual collision function for handling collisions with the player
	virtual void PlayerCollision(PhysicsObject *target) = 0;

	//This function is designed to be used by other objects to move this object around (with an offset) if necessary
	void OffsetSelf(CEngine::Vector2D offset);

protected:
	//boolean that states if the object is standing on solid ground.
	bool onSolidGround;

	//boolean used to set if an object is preventing the player from moving horizontally.
	bool hittingObject;

	//Object velocity
	float xVel,yVel;

	//Used to determine if the object needs to hitTest against other objects.
	bool isMoveable;
};
#endif