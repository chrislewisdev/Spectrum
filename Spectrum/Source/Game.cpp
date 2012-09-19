/*****************************************************************
*Spectrum
*Game.cpp by Chris Lewis & Joe Park
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
#include "Vector2D.h"
#include "Box2D.h"
#include "MoveableBlock.h"
#include "math.h"
#include <fstream>

using namespace std;
using namespace CEngine;

Game::Game(StateMachine *_Owner, GameData *_Storage)
	: GameState(_Owner, _Storage),
	player(Box2D(250,250,32,32)), exit(Box2D(0, 0, 32, 32), COLOUR_GREEN)
{
	ColouredObject::SetTorch(player.GetTorch());
}

//State Enter function
void Game::Enter()
{
	ColouredObject::SetCurrentColour(COLOUR_RED);

	//Load in our level list
	LoadLevelList("levels.txt");

	LoadNextMap();
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

	player.SetOnSolidGround(true);
	//Checking for collisions between moveable objects to be added
	if(WorldCollisionAbove(player.GetBounds()) && !player.GetOnSolidGround())
		player.ObjectAbove();
	else if(WorldCollisionBelow(player.GetBounds()) || player.GetStanding())
		player.ObjectBelow();
	else//falling
		player.SetOnSolidGround(false);

	//Check for Player movement inputs
	player.Update(deltaTime);
	
	//Set player to not standing by default.
	player.SetStanding(false);

	RemoveObjectOverlap();

	player.UpdateTorch();

	//Update all GameObjects
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		(*cdtr)->Update(deltaTime);
	}

	//Check for the player hitting the exit
	if (exit.CheckCollision(player.BoundingBox()))
	{
		//Load the next level
		LoadNextMap();
	}

	//Check for collisions between the player and the world
	PlayerWorldCollision();

	//Check for collisions between the player and the world
	if(WorldCollisionLeft(player.GetBounds()))
		player.ObjectLeft();
	else if(WorldCollisionRight(player.GetBounds()))
		player.ObjectRight();
	else
		player.SetHittingObject(false);

	//Draw all GameObjects
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		(*cdtr)->Draw();
	}
	exit.Draw();

	//Draw the player AFTER everything else to help with the alpha blending
	player.Draw();

	//Check for level reset input
	if (ProgramControl::ProgramInput.GetKey('r'))
	{
		LoadMap(currentMap);
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
void Game::PlayerWorldCollision()
{
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		PhysicsObject *collidee = dynamic_cast<PhysicsObject*>(cdtr->get());
		collidee->PlayerCollision(&player);
	}
}

//This function checks for collision against all objects in the world below the player
bool Game::WorldCollisionBelow(Box2D target)
{
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		if ((*cdtr)->CheckCollision(target) && //The target is overlapping against any object in the world
			target.pos.y <= (*cdtr)->BoundingBox().pos.y)//And the target is above the object
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
		if ((*cdtr)->CheckCollision(target) && //The target is overlapping against any object in the world
			target.pos.y >= (*cdtr)->BoundingBox().pos.y)//And the target is below the object
		{
			return true;
		}
	}
	return false;
}

//This function checks for collision against all objects in the world below the player
bool Game::WorldCollisionLeft(Box2D target)
{
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		if ((*cdtr)->CheckCollision(target) && //The target is overlapping against any object in the world
			target.pos.x <= (*cdtr)->BoundingBox().pos.x)//And the target is below the object
		{
			return true;
		}
	}
	return false;
}

//This function checks for collision against all objects in the world below the player
bool Game::WorldCollisionRight(Box2D target)
{
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		if ((*cdtr)->CheckCollision(target) && //The target is overlapping against any object in the world
			target.pos.x >= (*cdtr)->BoundingBox().pos.x)//And the target is below the object
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
	if (!Root.LoadFile()) throw std::runtime_error(string("Failed to open level file: ") + filename);

	//Get a handle to our first set of 'layer' data in the map. This could be anything from a tile/object layer to tileset info,
	//so we need to check what it is before we do anything with it.
	TiXmlElement *Layer = Root.FirstChildElement("map")->FirstChildElement();

	//Clear out any existing object data
	GameStorage->ClearAll();

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
			ColourType colour;

			//Convert name to lower-case
			for (int i = 0; i < name.length(); i++)
			{
				name[i] = tolower(name[i]);
			}

			//Loop through all objects
			while (Object)
			{
				string type((Object->Attribute("type") != NULL) ? Object->Attribute("type") : "");

				//Depending on the type of this layer, spawn a certain type of object
				if (name == "red")
				{
					colour = COLOUR_RED;
				}
				else if (name == "blue")
				{
					colour = COLOUR_BLUE;
				}
				else if (name == "yellow")
				{
					colour = COLOUR_YELLOW;
				}
				else if (name == "white")
				{
					colour = COLOUR_WHITE;
				}
				else if (name == "player")
				{
					player.ReadPosition(Object);
				}
				else if (name == "exit")
				{
					exit.ReadPosition(Object);
				}

				if (name != "player" && name != "exit")
				{
					if (type == "" || type == "normal")
					{
						GameStorage->AddObject(GameObjectPointer(new ColourBox(Object, colour)));
					}
					else if (type == "moveable")
					{

					}
					else if (type == "moving")
					{
						GameStorage->AddObject(GameObjectPointer(new MovingColourBlock(Object, colour)));
					}
				}

				Object = Object->NextSiblingElement();
			}
		}

		Layer = Layer->NextSiblingElement();
	}

	ColouredObject::SetCurrentColour(COLOUR_RED);
}

//This function loads our level list in from a file
void Game::LoadLevelList(string filename)
{
	//Try to open up our file for streaming
	fstream file(filename);

	//Check for successful opening
	if (file.bad()) 
	{
		MessageBox(NULL, "Couldn't open level list file.", "Error", MB_OK);
	}

	//Clear out our current list
	while (!levels.empty())
	{
		levels.pop();
	}

	string tempString;

	//Read in each of our level names
	while (!file.eof())
	{
		file >> tempString;
		levels.push(tempString);
	}
}

//This function loads the next map in our queue
void Game::LoadNextMap()
{
	if (levels.empty()) return;

	string nextMap = levels.front();

	LoadMap(nextMap);

	currentMap = nextMap;

	levels.pop();
}

void Game::RemoveObjectOverlap()
{		
	//Adjust the players position so they no longer overlap with an object below them.
	for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
	{
		int count = 0;
		while ((*cdtr)->CheckCollision(player.GetBounds()))
		{
			//Adjusts the players y value till it is no longer overlapping with the block. This allows us to test for
			//collisions in the horizontal domain without interference.
			player.AdjustPosition((*cdtr)->BoundingBox());

			//Since we have adjusted the players position this means that they are standing with an object below them
			//Set standing to true so that we can use that instead of checking for a collesion since this no longer works
			//Because the player isn't overlapping with the block.
			player.SetStanding(true);
			
			//Prevents an infinite loop.
			count++;
			if(count >= 10)
				break;
		}
	}
}