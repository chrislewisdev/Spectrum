/**************************************************************
*Spectrum
*Main.h by Chris Lewis
*Declares all main includes for the project
**************************************************************/

//Include guard
#ifndef MAIN_H
#define MAIN_H

//Include our required headers
//Windows.h- this file gives access to a bunch of Windows-specific functions and stuff
#include <windows.h>
//SDL- this takes care of the window creation and so on
#include <SDL.h>
//OpenGL headers, you get the idea
#include <gl/GL.h>
#include <gl/GLAux.h>
#include <gl/GLU.h>
#include <gl/glext.h>
//Other miscellaneous headers for certain functions/classes
#include <math.h>
#include <time.h>
#include <string.h>
/**************************************
You might notice the "vector" class being used throughout this code.
We haven't covered it in class, but should next semester.
Think of it as basically dynamic-memory management, except the hard work is done for us.
We just tell it when we want to add new items to a list, and it takes care of it.
**************************************/
#include <vector>

using namespace std;

//Define a PI constant
#define PI		3.14159

#endif