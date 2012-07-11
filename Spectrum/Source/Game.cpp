/*****************************************************************
*Spectrum
*Game.cpp by Chris Lewis
*****************************************************************/

#include "Game.h"
#include <ProgramControl.h>
#include "ColouredObject.h"
#include "Player.h"
#include <GameObject.h>
#include <Box2D.h>
#include <tinyxml.h>
#include <string>
#include "ColourBox.h"

using namespace std;
using namespace CEngine;

Game::Game(StateMachine *_Owner, GameData *_Storage)
	: GameState(_Owner, _Storage), player(Box2D(250,250,32,32))
{
	
}

//State Enter function
void Game::Enter()
{
	ColouredObject::SetCurrentColour(COLOUR_RED);
	
	//Load up our test map
	LoadMap("test_map.tmx");
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

	if(WorldCollisionBelow(player.GetBounds()))
	{
		player.setOnSolidGround(true);		
	}
	if(WorldCollisionAbove(player.GetBounds()))
	{
		//
	}
	else
	{
		player.setOnSolidGround(false);
	}
	//Apply gravity to the player every update.
	//player.ApplyGravity();
	//Check for Player movement inputs
	player.Move();

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

//This function checks for collision against all objects in the world below the player
bool Game::WorldCollisionBelow(Box2D target)
{
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		if ((*cdtr)->BoundingBox().Overlap(target) && target.pos.y >= (*cdtr)->BoundingBox().pos.y -
			player.GetBounds().size.y)
		{
			return true;
		}
	}
	return false;
}

//This function checks for collision against all objects in the world below the player
bool Game::WorldCollisionAbove(Box2D target)
{
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		if ((*cdtr)->BoundingBox().Overlap(target) && target.pos.y <= (*cdtr)->BoundingBox().pos.y +
			player.GetBounds().size.y)
		{
			return true;
		}
	}
	return false;
}
//This function loads a map from the specified .tmx file
void Game::LoadMap(string filename)
{
	//Create our Root Document handle and open it up
	TiXmlDocument Root(filename.c_str());
	if (!Root.LoadFile()) throw std::runtime_error("Failed to open level file.");

	//Get a handle to our first set of 'layer' data in the map. This could be anything from a tile/object layer to tileset info,
	//so we need to check what it is before we do anything with it.
	TiXmlElement *Layer = Root.FirstChildElement("map")->FirstChildElement();

	//Loop through all layers we can find in the map data
	while (Layer)
	{
		//Check for an object layer that has child elements. Currently this is the only kind we're interested in.
		if (string(Layer->Value()) == "objectgroup" && !Layer->NoChildren())
		{
			//Get our first object in this layer
			TiXmlElement *Object = Layer->FirstChildElement();
			//Get the name of our layer
			string name(Layer->Attribute("name"));

			//Loop through all objects
			while (Object)
			{
				//Depending on the type of this layer, spawn a certain type of object
				if (name == "red")
				{
					GameStorage->AddObject(GameObjectPointer(new ColourBox(Object, COLOUR_RED)));
				}
				else if (name == "blue")
				{
					GameStorage->AddObject(GameObjectPointer(new ColourBox(Object, COLOUR_BLUE)));
				}
				else if (name == "yellow")
				{
					GameStorage->AddObject(GameObjectPointer(new ColourBox(Object, COLOUR_YELLOW)));
				}
				else if (name == "white")
				{
					GameStorage->AddObject(GameObjectPointer(new ColourBox(Object, COLOUR_WHITE)));
				}

				Object = Object->NextSiblingElement();
			}
		}

		Layer = Layer->NextSiblingElement();
	}
}