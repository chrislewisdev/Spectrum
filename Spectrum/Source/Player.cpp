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
}

Player::~Player()
{

}

void Player::Move()
{
	//Check for vertical movement
	if (ProgramControl::ProgramInput.GetKey('w'))
	{
		//Jump();
	}
	else if (ProgramControl::ProgramInput.GetKey('a'))
	{
		bounds.pos.x -= playerMoveSpeed;
		
	}
	else if (ProgramControl::ProgramInput.GetKey('d'))
	{
		bounds.pos.x += playerMoveSpeed;
		
	}	
	bounds.pos.y += yVel;
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
	if(!CheckOnSolidGround())
	{
		bounds.pos.y += GRAVITY;
	}
}

void Player::Jump()
{
	//Checks that the player is on solid ground before they can jump
	if(CheckOnSolidGround())
	{		
		//Player is know travelling at a velocity -40 (upwards)
		yVel = -playerMoveSpeed*5;
	}
}

bool Player::CheckOnSolidGround()
{
	//Return result of the Players Bounding Box overlaping another object
	/*if(CEngine::Box2D.Overlap(BoundingBox()))?
	{
		//The player is standing on a block
		yVel = 0.0f;
		return true;
	}
	else
	{
		//The player is falling
		yVel = 5.0f;
		return false
	}*/
	return false;//Only here to allow function to compile
}