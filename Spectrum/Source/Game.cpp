/*****************************************************************
*Spectrum
*Game.cpp by Chris Lewis
*****************************************************************/

#include "Game.h"
#include <ProgramControl.h>
#include "ColouredObject.h"

using namespace CEngine;

Game::Game(StateMachine *_Owner, GameData *_Storage)
	: GameState(_Owner, _Storage)
{

}

//State Enter function
void Game::Enter()
{
	ColouredObject::SetCurrentColour(COLOUR_RED);
}

//State Update function
void Game::Update(float deltaTime)
{
	//Check for input on 1-2-3 for changing the current colour
	if (ProgramControl::ProgramInput.GetKey(SDLK_1))
		ColouredObject::SetCurrentColour(COLOUR_RED);
	else if (ProgramControl::ProgramInput.GetKey(SDLK_2))
		ColouredObject::SetCurrentColour(COLOUR_BLUE);
	else if (ProgramControl::ProgramInput.GetKey(SDLK_3))
		ColouredObject::SetCurrentColour(COLOUR_YELLOW);

	//Apply gravity to the player every update.
	player.ApplyGravity();

	//Check for Player movement inputs
	//Decided to use wasd since where using 1,2,3 to swap colours.
	if (ProgramControl::ProgramInput.GetKey('a'))
	{
		player.Move();
	}
	else if (ProgramControl::ProgramInput.GetKey('d'))
	{
		player.Move();		
	}
	else if (ProgramControl::ProgramInput.GetKey('w'))
	{
		player.Move();
	}

	//Update all GameObjects
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		(*cdtr)->Update(deltaTime);
	}

	player.Draw();

	//Draw all GameObjects
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		(*cdtr)->Draw();
	}
}

//State Exit function
void Game::Exit()
{
	//Nothing required currently
}

//State Clone function
State *Game::Clone(StateMachine *NewOwner) const
{
	return new Game(NewOwner, GameStorage);
}

//This function checks for collision against all objects in the world
bool Game::WorldCollision(Box2D target)
{
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		if ((*cdtr)->BoundingBox().Overlap(target)) return true;
	}

	return false;
}