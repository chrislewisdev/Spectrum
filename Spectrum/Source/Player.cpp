/*****************************************************************
*Spectrum
*Player.cpp by Joe Park
*****************************************************************/
#include "Player.h"
#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>

Player::Player()
{

}
Player::Player(CEngine::Box2D boundingBox, float _xPos, float _yPos)
{
	xPos = _xPos;
	yPos = _yPos;
}

Player::~Player()
{

}

void Player::Move()
{
	//Note: You should be using ProgramControl::ProgramInput.GetKey here, and just calling Player::Move() once from Game::Update
	//Check for vertical movement
	if(SDLK_UP)
	{
		Jump();
	}
	//Check for horizontal movement
	if (SDLK_LEFT)
	{
		xVel -= playerMoveSpeed;
	}
	else if (SDLK_RIGHT)
	{
		xVel += playerMoveSpeed;
	}

	//If we're jumping slow down the horizontal speed
	if (xVel != 0.0f && yVel != 0)
	{
		xVel /= 1.5f;
	}
	xPos += xVel;
	yPos += yVel;
}

//This function will draw the player
void Player::Draw()
{
	//Draw our player-position point
	glColor3f(10.0f, 10.0f, 10.0f);
	DrawBoundingBox();
}

void Player::ApplyGravity()
{
	//Checks if the player is falling, if they are apply gravity.
	if(!CheckOnSolidGround())
	{
		yVel -= GRAVITY;
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
	return true;//Only here to allow function to compile
}