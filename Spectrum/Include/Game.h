/*******************************************************************
*Spectrum
*Game.h by Chris Lewis
*******************************************************************/

#ifndef SPECTRUM_GAME_H
#define SPECTRUM_GAME_H

#include <GameState.h>
#include "Player.h"


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

private:
	//Creates the player
	Player player;
};

#endif