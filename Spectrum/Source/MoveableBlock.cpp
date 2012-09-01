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

void MoveableBlock::Update(float deltaTime)
{
	//ApplyGraivty();
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

bool MoveableBlock::CheckIfMovementKeyIsDown()
{
	if (ProgramControl::ProgramInput.GetKey('w'))
		return true;
	/*if (ProgramControl::ProgramInput.GetKey('a'))
		return true;
	if (ProgramControl::ProgramInput.GetKey('d'))
		return true;*/
	else
		return false;
}

void MoveableBlock::PlayerCollision(PhysicsObject *target)
{
	Box2D collisionArea = bounds;
	collisionArea.pos.y -= 2;

	if (collisionArea.Overlap(target->BoundingBox()))
	{
		if(CheckIfMovementKeyIsDown())
		{
			if(target->BoundingBox().pos.x >= bounds.pos.x)//Player to the right of object
			{
				bounds.pos.x -= 4.0;
			}
			else
			{
				bounds.pos.x += 4.0;
			}
		}
		
	}
}