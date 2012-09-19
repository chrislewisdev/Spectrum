/*******************************************************************
*Spectrum
*Game.h by Chris Lewis & Joe Park
*******************************************************************/

#ifndef SPECTRUM_GAME_H
#define SPECTRUM_GAME_H

#include <GameState.h>
#include "Player.h"
#include "MovingColourBlocks.h"
#include "Vector2D.h"
#include "Box2D.h"
#include "Sprite.h"
#include <queue>

class Game : public CEngine::GameState
{
public:
	Game(CEngine::StateMachine *_Owner, CEngine::GameData *_Storage);

	//Declare public functions
	//State Enter function
	void Enter();
	//State Update function
	void Update(float deltaTime);
	//State Exit function
	void Exit();
	//State Clone function
	CEngine::State *Clone(CEngine::StateMachine *NewOwner) const;

	//This function checks if the target collides with anything in the world
	void PlayerWorldCollision();
	//This function checks if the target collides with anything below it in the world
	bool WorldCollisionBelow(CEngine::Box2D target);
	//This function checks if the target collides with anything above it in the world
	bool WorldCollisionAbove(CEngine::Box2D target);
	//This function checks if the target collides with anything to the left of it in the world
	bool WorldCollisionLeft(CEngine::Box2D target);
	//This function checks if the target collides with anything to the right of it in the world
	bool WorldCollisionRight(CEngine::Box2D target);	


	//This function loads a map from the specified .tmx file
	void LoadMap(std::string filename);
	//This function loads the level list from a file
	void LoadLevelList(std::string filename);

private:
	//Creates the player
	Player player;
	//Queue of level names to load
	std::queue<std::string> levels;
	//ColourBox Marker for the level exit
	ColourBox exit;

	void RemoveObjectOverlap();

	//Loads the next map in the level queue
	void LoadNextMap();
};

#endif