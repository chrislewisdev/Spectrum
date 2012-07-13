/******************************************************************
*Spectrum
*Torch.h by Chris Lewis
******************************************************************/

#ifndef SPECTRUM_TORCH_H
#define SPECTRUM_TORCH_H

#include <Box2D.h>
#include <Circle2D.h>

class Torch
{
public:
	Torch(CEngine::Vector2D p);

	//Declare public functions
	//Checks if the torch is overlapping with the target box
	bool Overlap(const CEngine::Box2D& target) const;
	//Sets the center position of our torch
	void SetPosition(CEngine::Vector2D p);
	//Makes our torch face the target point
	void FacePoint(CEngine::Vector2D target);
	//Draws our torch
	void Draw();

private:
	//Circle representing our overall area
	CEngine::Circle2D area;
	//Angle dictating the center position of our arc
	float angle;
	//Angle dictating how 'wide' our arc is
	const float angleWidth;
};

#endif