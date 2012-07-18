/*******************************************************************
*Spectrum
*Torch.cpp by Chris Lewis
*******************************************************************/

#include "Torch.h"
#include <CEMath.h>
#include <Windows.h>
#include <gl/GL.h>
#include <Collision.h>

using namespace CEngine;

Torch::Torch(Vector2D p)
	: area(p, 100), angle(0), angleWidth(70)
{

}

//Checks if our torch is overlapping with the target box
bool Torch::Overlap(const Box2D& target) const
{
	//Find the closest point on the box to our circle
	Vector2D p = area.pos;
	if (p.x < target.pos.x) p.x = target.pos.x;
	else if (p.x > target.pos.x + target.size.x) p.x = target.pos.x + target.size.x;
	if (p.y < target.pos.y) p.y = target.pos.y;
	else if (p.y > target.pos.y + target.size.y) p.y = target.pos.y + target.size.y;

	//Now, check if this point is within our arc area (taking into account the possible wrapping of angle values)
	float a = Math::Angle(area.pos, p);
	float start = angle - angleWidth/2, end = angle + angleWidth/2;
	if (a > start && a < end || a + 360 > start && a + 360 < end || a - 360 > start && a - 360 < end)
	{
		//If it's within our area, just check that we contain this point
		return area.Contains(p);
	}
	
	//Otherwise, we need to check at the edges of our arc to see if any point still intersects
	Ray2D edge1(area.pos, Math::AngledVector(start, area.radius));
	Ray2D edge2(area.pos, Math::AngledVector(end, area.radius));

	//If either of these edges intersect with the box, we should return true
	return (Collision::RayBoxIntersection(edge1, target) != Collision::NoIntersection || Collision::RayBoxIntersection(edge2, target) != Collision::NoIntersection);
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