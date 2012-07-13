/*******************************************************************
*Spectrum
*Torch.cpp by Chris Lewis
*******************************************************************/

#include "Torch.h"
#include <CEMath.h>
#include <Windows.h>
#include <gl/GL.h>

using namespace CEngine;

Torch::Torch(Vector2D p)
	: area(p, 100), angle(0), angleWidth(70)
{

}

//Checks if our torch is overlapping with the target box
bool Torch::Overlap(const Box2D& target) const
{
	return false;
}

//Sets the center position of our torch
void Torch::SetPosition(Vector2D p)
{
	area.pos = p;
}

//Makes our torch face a specific point
void Torch::FacePoint(Vector2D target)
{
	angle = Math::Angle(area.pos, target);
}

//Draws our Torch to the screen
void Torch::Draw()
{
	glBegin(GL_POLYGON);
		glVertex2f(area.pos.x, area.pos.y);
		Vector2D p;
		for (float a = angle - angleWidth/2; a < angle + angleWidth/2; a++)
		{
			p = area.pos + Math::AngledVector(a, area.radius);
			glVertex2f(p.x, p.y);
		}
	glEnd();
}