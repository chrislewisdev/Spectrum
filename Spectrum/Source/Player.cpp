/*****************************************************************
*Spectrum
*Player.cpp by Joe Park & Chris Lewis
*****************************************************************/
#include "Player.h"
#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <ProgramControl.h>
#include "Game.h"

using namespace CEngine;

Player::Player()
	: torch(Vector2D(0, 0)), PhysicsObject(bounds)
{

}

Player::Player(Box2D _boundingBox)
	: torch(_boundingBox.pos + _boundingBox.size/2), PhysicsObject(_boundingBox)
{	
	jumping = false;
	frameCount = 0;
}

Player::~Player()
{

}

void Player::Move()
{	
	//Check for vertical movement
	if (ProgramControl::ProgramInput.GetKey('w'))
	{
		if(onSolidGround == true)
		{
			yVel += GRAVITY * 1.5f;
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

//This function returns a const pointer to the Player's torch
const Torch *Player::GetTorch() const
{
	return &torch;
}
