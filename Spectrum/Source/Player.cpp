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
	: torch(Vector2D(0, 0))
{

}

Player::Player(Box2D _boundingBox)
	: torch(_boundingBox.pos + _boundingBox.size/2)
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

void Player::setOnSolidGround(bool _onSolidGround)
{
	onSolidGround = _onSolidGround;
}

void Player::setJumping(bool _jumping)
{
	jumping = _jumping;
}

void Player::setyVel(float _yVel)
{
	yVel = _yVel;
}

void Player::Move()
{	
	//Check for vertical movement
	if (ProgramControl::ProgramInput.GetKey('w'))
	{
		if(onSolidGround == true)
		{
			yVel += GRAVITY;
			jumping = true;
		}		
	}
	if (ProgramControl::ProgramInput.GetKey('a'))
	{
		bounds.pos.x -= xVel;		
	}
	if (ProgramControl::ProgramInput.GetKey('d'))
	{
		bounds.pos.x += xVel;		
	}

	//If jumping has been set to true call jump
	if(jumping == true)
	{
		Jump();
	}

	//Apply gravity to the player every update.	
	ApplyGravity();

	xVel = playerMoveSpeed;	
=======
	//Make sure the torch stays centered on our character
	torch.SetPosition(bounds.pos + bounds.size/2);
	//Make the torch face the direction of the cursor
	torch.FacePoint(ProgramControl::ProgramInput.GetMousePosition());
}

//This function will draw the player
void Player::Draw()
{
	//Draw our player-position point
	glColor3f(.5f, 0, 0);
	DrawBoundingBox();
	glEnable(GL_BLEND);
	glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
	torch.Draw();
	glDisable(GL_BLEND);
}

void Player::ApplyGravity()
{
	//Checks if the player is falling, if they are apply gravity.
	if(!onSolidGround && !jumping)
	{
		bounds.pos.y += GRAVITY;
	}
}

void Player::Jump()
{
	frameCount++;
	//Checks that the allowed amount of frames has passed before you begin to fall.
	if(frameCount <= 15)
	{		
		bounds.pos.y -= yVel;
		jumping = true;
	}
	else
	{
		//Jumping finished begin to fall.
		yVel = 0;
		frameCount = 0;
		jumping = false;
	}	
}

void Player::ObjectBelow()
{
	//Set onSolidGround to true since you have collided with an object below you.
	onSolidGround = true;

	//Set yVel to 0 so you stop falling
	yVel = 0;
}

void Player::ObjectAbove()
{
	//Set onSolidGround to false since you cant be on solid ground if you've hit something above you.
	onSolidGround = false;

	//Set yVel to Gravity so that you begin to fall downwards.
	yVel += GRAVITY;
}
