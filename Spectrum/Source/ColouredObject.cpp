/*****************************************************************
*Spectrum
*ColouredObject.cpp by Chris Lewis
*****************************************************************/

#include "ColouredObject.h"

using namespace CEngine;

//Define our static currentColour variable
ColourType ColouredObject::currentColour = COLOUR_NONE;

ColouredObject::ColouredObject(Box2D boundingBox, ColourType c)
	: GameObject(boundingBox), colour(c)
{

}

//This function sets the current colour selected by the game
void ColouredObject::SetCurrentColour(ColourType c)
{
	currentColour = c;
}

//This function returns the current colour selected by the game
ColourType ColouredObject::CurrentColour()
{
	return currentColour;
}

//This function returns the colour of this object
ColourType ColouredObject::Colour() const
{
	return colour;
}