#ifndef PhysicsObject_H
#define PhysicsObject_H

#include <GameObject.h>
#include "Box2D.h"

class PhysicsObject: public CEngine::GameObject
{
public:
	PhysicsObject();
	PhysicsObject(CEngine::Box2D _boundingBox);
	virtual ~PhysicsObject();

	CEngine::Box2D GetBounds() const;

	void SetOnSolidGround(bool _onSolidGround);
	void SetXVel(float _xVel);
	void SetYVel(float _yVel);	

	//Apply Gravity to the object
	virtual void ApplyGravity();

	virtual void Move() = 0;

	//The function that handles a collesion with an object below you
	void ObjectBelow();

	//The function that handles a collesion with an object above you
	void ObjectAbove();

protected:
	//boolean that states if the object is standing on solid ground.
	bool onSolidGround;

	//Object velocity
	float xVel,yVel;
};
#endif