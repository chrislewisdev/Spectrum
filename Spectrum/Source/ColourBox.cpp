/*******************************************************************
*Spectrum
*ColourBox.cpp by Chris Lewis
********************************************************************/

#include "ColourBox.h"
#include <Windows.h>
#include <gl/gl.h>

using namespace CEngine;

ColourBox::ColourBox(Box2D boundingBox, ColourType c)
	: ColouredObject(boundingBox, c)
{

}

//This function updates our object
void ColourBox::Update(float deltaTime)
{

}

//This function draws our object
void ColourBox::Draw()
{
	//Only draw this block if we have the current selected colour
	if (colour == CurrentColour() || colour == COLOUR_WHITE)
	{
		if (colour == COLOUR_RED) glColor3f(1.0f, 0.0f, 0.0f);
		else if (colour == COLOUR_BLUE) glColor3f(0.0f, 0.0f, 1.0f);
		else if (colour == COLOUR_YELLOW) glColor3f(1.0f, 1.0f, 0.0f);
		else if (colour == COLOUR_WHITE) glColor3f(1.0f, 1.0f, 1.0f);

		DrawBoundingBox();
	}
}

//Clone function
GameObject *ColourBox::Clone() const
{
	return new ColourBox(*this);
}