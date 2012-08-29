/*****************************************************************
*Spectrum
*MoveableBlock.cpp by Joe Park
*****************************************************************/
#include "MoveableBlock.h"
#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <ProgramControl.h>
#include "PhysicsObject.h"

using namespace CEngine;

MoveableBlock::MoveableBlock(Box2D boundingBox)
	: PhysicsObject(boundingBox, COLOUR_WHITE)
{
	onSolidGround = false;
}

void MoveableBlock::Collision(float playerXPos, float playerXVel)
{
	if(playerXPos >= bounds.pos.x)
	{
		bounds.pos.x -= playerXVel;
	}
	else if(playerXPos <= bounds.pos.x)
	{
		bounds.pos.x += playerXVel;
	}
}

void MoveableBlock::ApplyGraivty()
{
	//Checks if the block is falling, if they are apply gravity.
	if(!onSolidGround)
	{
		bounds.pos.y += GRAVITY;
	}
}

//This function will draw the block
void MoveableBlock::Draw()
{
	//Draw our block-position point
	glColor3f(.5f, 0, 0);
	DrawBoundingBox();
}

void MoveableBlock::PlayerCollision(PhysicsObject *target)
{
	//Do nothing for now
}