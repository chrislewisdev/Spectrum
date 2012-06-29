/******************************************************************
*CEngine
*GameState.h by Chris Lewis
*Defines abstract subclass of State specific to Game control
*******************************************************************/

#ifndef CENGINE_GAMESTATE_H
#define CENGINE_GAMESTATE_H

//Include State header
#include "State.h"

//Declare inside the CEngine namespace
namespace CEngine
{
	class GameData;

	/// \brief Abstract class as a slight expansion of State to use for Game Logic control
	///
	/// The GameState class inherits off of State and has one added member: a pointer to a GameData instance that can be used for 
	/// accessing and controlling game objects.
	class GameState : public State
	{
	public:
		//! Single constructor to initialise our Game Owner
		GameState(StateMachine *_GameOwner, GameData *_GameStorage) : State(_GameOwner), GameStorage(_GameStorage) {};

	protected:
		//Declare protected members
		//! Pointer to our GameData storage
		GameData *GameStorage;
	};
}

#endif