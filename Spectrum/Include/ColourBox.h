/*******************************************************************
*Spectrum
*ColourBox.h by Chris Lewis
*******************************************************************/

#ifndef SPECTRUM_COLOURBOX_H
#define SPECTRUM_COLOURBOX_H

#include "ColouredObject.h"

class ColourBox : public ColouredObject
{
public:
	ColourBox(CEngine::Box2D boundingBox, ColourType c);

	//Declare public functions
	//GameObject Update function
	void Update(float deltaTime);
	//GameObject Draw function
	void Draw();
	//GameObject Clone function
	CEngine::GameObject *Clone() const;
};

#endif