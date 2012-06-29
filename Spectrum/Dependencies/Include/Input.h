/*************************************************************
*CEngine
*Input.h by Chris Lewis
*Declares the Input class for storing/accessing current user input
*************************************************************/

#ifndef CENGINE_INPUT_H
#define CENGINE_INPUT_H

//Include any headers we need
#include <SDL.h>
#include <stdexcept>
#include "Vector2D.h"

namespace CEngine
{
	/// \brief Designed to handle all necessary input for an application. Covers keyboard input and mouse input.
	///
	/// The Input class is designed to be used by the ProgramControl class to process keyboard event messages and
	/// store input values accordingly. Other classes are to use the Get methods to retrieve whatever information they need.
	/// Currently only core input features are supported- that is, all ASCII characters, and three mouse buttons.
	/// More possibilities are certainly possible but will be looked into with further testing.
	class Input
	{
	public:
		//! Default Constructor
		Input();

		//Declare exception classes
		/// \brief Exception class to indicate that an invalid key index was passed to GetKey.
		///
		/// Thrown only by GetKey when an invalid index (<0 or >322) is passed as an argument.
		class KeyIndexException : public std::exception
		{
		public:
			KeyIndexException(const char *what) : std::exception(what) {}
		};

		//Declare public functions
		/// \brief Processes an SDL event, checking for messages relevant to input
		///
		/// \param e The SDL Event structure to check.
		/// \return true if the event was handled, false if the event was not an input-related event
		bool ProcessEvent(SDL_Event e);
		/// \brief Retrieves the current status of the key denoted by char value c.
		///
		/// \param c The char value to check for. May also be an SDL-defined keysym value.
		/// \return The true/false state of the key.
		bool GetKey(int c) const;
		/// \brief Retrieves the mouse position in screen co-ordinates.
		///
		/// \return A Vector2D denoting its position, relative to the top left of the window.
		Vector2D GetMousePosition() const;
		/// \brief Retrieves the button state of a specific mouse button.
		///
		/// \param id The ID of the mouse button to check. Should be SDL_BUTTON_LEFT/MIDDLE/RIGHT
		/// \return The true/false state of the button
		bool GetMouseDown(int id) const;

	private:
		//Declare private functions
		//! Process a keyboard event and sets our key-states accordingly.
		void ProcessKeys(SDL_KeyboardEvent e);
		//! Process a Mouse Motion event to set our mouse position.
		void ProcessMouseMove(SDL_MouseMotionEvent e);
		//! Process a Mouse Down event to set our mouse button states.
		void ProcessMouseDown(SDL_MouseButtonEvent e);

		//Declare private properties
		//Storage for key statuses- can hold all possible SDLKey values
		bool keys[SDLK_LAST];
		//Current position of the mouse
		Vector2D mousePosition;
		//Mouse button states
		bool leftMouseDown, midMouseDown, rightMouseDown;
	};


	/// \example Examples/ExampleInput.cpp
	/// Demonstrates usage of the Input class via the ProgramControl class. Covers all basic types of input (keyboard, mouse).
}

#endif