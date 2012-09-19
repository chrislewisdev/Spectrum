/*******************************************************************
*Spectrum
*Entry.cpp by Chris Lewis
*******************************************************************/

#include <Windows.h>
#include <ProgramControl.h>
#include "StateID.h"
#include "Game.h"
#include "ColourBox.h"
#include <Windows.h>
#include <gl/GL.h>
#include <il/il.h>
#include <il/ilu.h>
#include <il/ilut.h>

using namespace CEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Create our Game Control and Window
	ProgramControl Control("Spectrum", 800, 600);
	GameData& Objects = *Control.GetGameData();

	glEnable(GL_TEXTURE_2D);

	//Set up alpa-blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	//Set up our GameState in our program
	Control.AddState(STATE_GAME, StatePointer(new Game(&Control, Control.GetGameData())));
	Control.ChangeState(STATE_GAME);

	//Set up some temporary colour boxes
	/*Box2D temp(64, 256, 128, 32);
	Objects.AddObject(GameObjectPointer(new ColourBox(temp, COLOUR_WHITE)));
	temp.pos.x = 480; temp.pos.y = 256; temp.size.x = 128;
	Objects.AddObject(GameObjectPointer(new ColourBox(temp, COLOUR_WHITE)));
	temp.pos.x = 192; temp.pos.y = 320; temp.size.x = 96;
	Objects.AddObject(GameObjectPointer(new ColourBox(temp, COLOUR_WHITE)));
	temp.pos.x = 64; temp.pos.y = 384; temp.size.x = 640;
	Objects.AddObject(GameObjectPointer(new ColourBox(temp, COLOUR_WHITE)));
	temp.pos.x = 288; temp.pos.y = 320; temp.size.x = 64;
	Objects.AddObject(GameObjectPointer(new ColourBox(temp, COLOUR_RED)));
	temp.pos.x = 352; temp.pos.y = 320; temp.size.x = 64;
	Objects.AddObject(GameObjectPointer(new ColourBox(temp, COLOUR_BLUE)));
	temp.pos.x = 416; temp.pos.y = 320; temp.size.x = 64;
	Objects.AddObject(GameObjectPointer(new ColourBox(temp, COLOUR_YELLOW)));*/

	//Start up our main game loop
	while (!Control.IsExiting() && !ProgramControl::ProgramInput.GetKey(VK_ESCAPE))
	{
		Control.GetWindow()->ClearScreen();

		Control.Update(Control.TimeSinceLastUpdate());

		Control.GetWindow()->UpdateScreen();

		//Make sure our loop time never goes below 10ms
		while (Control.TimeSinceLastUpdate() < 0.01f) {Sleep(1);}
	}

	return 0;
}