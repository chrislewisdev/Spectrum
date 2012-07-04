/*****************************************************************
*Spectrum
*Player.cpp by Joe Park
*****************************************************************/
#include "Player.h"
#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <ProgramControl.h>

using namespace CEngine;

Player::Player()
{

}

Player::Player(Box2D _boundingBox)
{
	bounds = _boundingBox;
	xVel = 0;
	yVel = 0;
	onSolidGround = false;
	jumping = false;
	frameCount = 0;
}

Player::~Player()
{

}

CEngine::Box2D Player::GetBounds() const
{
	return bounds;
}

void Player::setOnSolidGround(bool _OnSolidGround)
{
	onSolidGround = _OnSolidGround;
}

void Player::Move()
{	
	//Check for vertical movement
	if (ProgramControl::ProgramInput.GetKey('w'))
	{
		if(onSolidGround == true)
		{
			jumping = true;
		}		
	}
	if (ProgramControl::ProgramInput.GetKey('a'))
	{
		bounds.pos.x -= playerMoveSpeed;		
	}
	if (ProgramControl::ProgramInput.GetKey('d'))
	{
		bounds.pos.x += playerMoveSpeed;		
	}

	//If jumping has been set to true call jump
	if(jumping == true)
	{
		Jump();
	}

	//Apply gravity to the player every update.	
	ApplyGravity();
}

//This function will draw the player
void Player::Draw()
{
	//Draw our player-position point
	glColor3f(.5f, 0, 0);
	DrawBoundingBox();	
}

void Player::ApplyGravity()
{
	//Checks if the player is falling, if they are apply gravity.
	if(!onSolidGround && !jumping)
	{
		bounds.pos.y += playerMoveSpeed;
	}
}

void Player::Jump()
{
	frameCount++;
	//Checks that the player is on solid ground before they can jump
	if(frameCount <= 15)
	{		
		bounds.pos.y -= playerMoveSpeed*2;
		jumping = true;
	}
	else
	{
		frameCount = 0;
		jumping = false;
	}	
}