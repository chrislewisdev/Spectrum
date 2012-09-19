/*******************************************************************
*Spectrum
*ColourBox.h by Chris Lewis
*******************************************************************/

#ifndef SPECTRUM_COLOURBOX_H
#define SPECTRUM_COLOURBOX_H

#include "ColouredObject.h"
#include "PhysicsObject.h"
#include <tinyxml.h>
#include "Sprite.h"

class ColourBox : public PhysicsObject
{
public:
	ColourBox(CEngine::Box2D boundingBox, ColourType c);
	//Constructor to take properties from a TinyXML object element
	ColourBox(TiXmlElement *Object, ColourType c);
	~ColourBox();

	//Declare public functions
	//GameObject Update function
	void Update(float deltaTime);
	//GameObject Draw function
	void Draw();
	//GameObject Clone function
	CEngine::GameObject *Clone() const;
	//Collision function for boxes- namely, the player (we want to make sure it takes current colour into account)
	bool CheckCollision(const CEngine::Box2D& target);
	//Player Collision function (inherited off of PhysicsObject)
	void PlayerCollision(PhysicsObject *target);

protected:
	//Declare protected functions
	//This function draws our sprite
	void DrawSprite();

private:
	//Declare private functions
	void DetermineColour();

	//Declare private properties
	//Colour values for this box
	float r, g, b;
	//Our sprite
	Sprite *sprite;
};

#endif