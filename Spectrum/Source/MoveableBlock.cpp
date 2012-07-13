/*****************************************************************
*Spectrum
*MoveableBlock.cpp by Joe Park
*****************************************************************/
#include "MoveableBlock.h"
#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <ProgramControl.h>

MoveableBlock::MoveableBlock(CEngine::Box2D boundingBox)
{
	bounds = boundingBox;
	onSolidGround = false;
}

void MoveableBlock::Push(float playerXPos, float playerXVel)
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

void MoveableBlock::Pull(float playerXPos, float playerXVel)
{
	if(playerXPos >= bounds.pos.x)
	{
		bounds.pos.x += playerXVel;
	}
	else if(playerXPos <= bounds.pos.x)
	{
		bounds.pos.x -= playerXVel;
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