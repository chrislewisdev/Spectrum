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
	bool WorldCollision(CEngine::Box2D target);
	//This function checks if the target collides with anything in the world
	bool WorldCollisionBelow(CEngine::Box2D target);
	//This function checks if the target collides with anything in the world
	bool WorldCollisionAbove(CEngine::Box2D target);
	//This function loads a map from the specified .tmx file
	void LoadMap(std::string filename);

private:
	//Creates the player
	Player player;
};

#endif