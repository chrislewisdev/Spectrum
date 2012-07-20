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
	if (colour == COLOUR_RED)
	{
		r = 1.0f; g = 0.0f; b = 0.0f;
	}
	else if (colour == COLOUR_BLUE)
	{
		r = 0.0f; g = 0.0f; b = 1.0f;
	}
	else if (colour == COLOUR_YELLOW)
	{
		r = 1.0f; g = 1.0f; b = 0.0f;
	}
	else if (colour == COLOUR_WHITE)
	{
		r = 1.0f; g = 1.0f; b = 1.0f;
	}
}

ColourBox::ColourBox(TiXmlElement *Object, ColourType c)
	: ColouredObject(c)
{
	//Temp storage for queried XML attribute values
	//Tiled stores all its co-ordinates as int so we use that even though our position data is stored as a float
	int tempValue;

	//Retrieve position and size values from our XML data
	//There should ideally be some checking here, but since we're reading from Tiled we can guarantee that this data exists in the right format.
	Object->QueryIntAttribute("x", &tempValue); bounds.pos.x = (float)tempValue;
	Object->QueryIntAttribute("y", &tempValue); bounds.pos.y = (float)tempValue;
	Object->QueryIntAttribute("width", &tempValue); bounds.size.x = (float)tempValue;
	Object->QueryIntAttribute("height", &tempValue); bounds.size.y = (float)tempValue;
}

//This function updates our object
void ColourBox::Update(float deltaTime)
{

}

//This function draws our object
void ColourBox::Draw()
{
	//Only draw this block if we have the current selected colour
	glEnable(GL_BLEND);
	if (colour == CurrentColour() || colour == COLOUR_WHITE)
	{
		glColor4f(r, g, b, 1.0f);

		DrawBoundingBox();
	}
	else if (PlayerTorch->Overlap(bounds))
	{
		glColor4f(r, g, b, 0.25f);

		DrawBoundingBox();
	}
	glDisable(GL_BLEND);
}

//Clone function
GameObject *ColourBox::Clone() const
{
	return new ColourBox(*this);
}

//This function checks for collision against a box whilst taking colour into account
bool ColourBox::CheckCollision(const Box2D& target)
{
	return (bounds.Overlap(target) && (colour == CurrentColour() || colour == COLOUR_WHITE));
}