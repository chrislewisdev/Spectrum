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
	: torch(Vector2D(0, 0)), PhysicsObject(COLOUR_WHITE)
{

}

Player::Player(Box2D _boundingBox)
	: torch(_boundingBox.pos + _boundingBox.size/2), PhysicsObject(_boundingBox, COLOUR_WHITE)
{	
	jumping = false;
	frameCount = 0;
	hittingObject = false;
	standing = false;
}

Player::~Player()
{

}

bool Player::GetJumping() const
{
	return jumping;
}

bool Player::GetStanding() const
{
	return standing;
}

void Player::SetStanding(bool _standing)
{
	standing = _standing;
}

void Player::Update(float deltaTime)
{
	xVel = 0;
	//Check for vertical movement
	if (ProgramControl::ProgramInput.GetKey('w'))
	{
		if(onSolidGround == true)
		{
			jumping = true;
		}
	}
	if (ProgramControl::ProgramInput.GetKey('a') && !hittingObject)
	{
		xVel = -playerMoveSpeed;		
	}
	if (ProgramControl::ProgramInput.GetKey('d') && !hittingObject)
	{
		xVel = playerMoveSpeed;			
	}

	//If jumping has been set to true call jump
	if(jumping == true)
	{
		Jump();
	}

	//Apply gravity to the player every update.	
	ApplyGravity();	

	bounds.pos.x += xVel*deltaTime*60;
	bounds.pos.y += yVel*deltaTime*60;
}

//This function updates the torch's position
void Player::UpdateTorch()
{
	//Make sure the torch stays centered on our character
	torch.SetPosition(bounds.pos + bounds.size/2);
	//Make the torch face the direction of the cursor
	torch.FacePoint(ProgramControl::ProgramInput.GetMousePosition());
}

//This function will draw the player
void Player::Draw()
{
	//Draw our player-position point
	glColor3f(1,1,1);
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
		yVel = GRAVITY;
	}
}

void Player::Jump()
{
	frameCount++;
	//Checks that the allowed amount of frames has passed before you begin to fall.
	if(frameCount <= 24)
	{	
		//Checking if removing floating point velocity fixes "getting stuck" issue.
		int jumpVelocity = -10 - (-GRAVITY*frameCount)/13;
		yVel = jumpVelocity;
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

void Player::ObjectAbove()
{
	//Set onSolidGround to false since you cant be on solid ground if you've hit something above you.
	onSolidGround = false;

	//Set yVel to Gravity so that you begin to fall downwards.
	yVel = 0;

	//Player is no longer jumping set jumping to false.
	jumping = false;
	frameCount = 0;
}

void Player::ObjectLeft()
{
	hittingObject = true;
	bounds.pos.x -= 4.0;
}

void Player::ObjectRight()
{
	hittingObject = true;
	bounds.pos.x += 4.0;
}

//This function loads the player's position from Tiled XML
void Player::ReadPosition(TiXmlElement *Object)
{
	int tempValue;

	Object->QueryIntAttribute("x", &tempValue); bounds.pos.x = tempValue;
	Object->QueryIntAttribute("y", &tempValue); bounds.pos.y = tempValue;
}

//This function should never get called!
void Player::PlayerCollision(PhysicsObject *target)
{
	//Do nothing!
}