/*******************************************************************
*Spectrum
*Entry.cpp by Chris Lewis
*******************************************************************/

#include <Windows.h>
#include <ProgramControl.h>
#include "StateID.h"
#include "Game.h"
#include "ColourBox.h"

using namespace CEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Create our Game Control and Window
	ProgramControl Control("Spectrum", 800, 600);
	GameData& Objects = *Control.GetGameData();

	//Set up our GameState in our program
	Control.AddState(STATE_GAME, StatePointer(new Game(&Control, Control.GetGameData())));
	Control.ChangeState(STATE_GAME);

	//Start up our main game loop
	while (!Control.IsExiting())
	{
		Control.GetWindow()->ClearScreen();

		Control.Update(Control.TimeSinceLastUpdate());

		Control.GetWindow()->UpdateScreen();

		//Make sure our loop time never goes below 10ms
		while (Control.TimeSinceLastUpdate() < 0.01f) {Sleep(1);}
	}

	return 0;
}