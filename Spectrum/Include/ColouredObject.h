/********************************************************************
*Spectrum
*ColouredObject.h by Chris Lewis
********************************************************************/

#ifndef SPECTRUM_COLOUREDOBJECT_H
#define SPECTRUM_COLOUREDOBJECT_H

#include <GameObject.h>
#include "ColourType.h"

class ColouredObject : public CEngine::GameObject
{
public:
	ColouredObject(ColourType c);
	ColouredObject(CEngine::Box2D boundingBox, ColourType c);

	//Declare public functions
	//Sets the current colour selected by the game
	static void SetCurrentColour(ColourType c);
	//Retrieves the current colour selected by the game
	static ColourType CurrentColour();
	//Returns the colour in use by this object
	ColourType Colour() const;

protected:
	//Declare protected properties
	//Specifier for what our colour type is
	ColourType colour;

private:
	//Declare private properties
	//Specifier for the game's current selected colour
	static ColourType currentColour;
};

#endif