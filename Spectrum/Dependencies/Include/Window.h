/**************************************************
*CEngine
*Window.h by Chris Lewis
*Declaration for Window class
*Handles window creation and OpenGL setup
**************************************************/

//Include guard
#ifndef CENGINE_WINDOW_H
#define CENGINE_WINDOW_H

//Include any necessary headers
#include <stdexcept>

//Declare our class in the CEngine namespace
namespace CEngine
{
	/// \brief Class for creating and managing an OpenGL Window.
	///
	/// The Window class is responsible for creating and destroying and OpenGL window with SDL.
	/// It is also responsible for initialising SDL (at the start of a program) and can be used to update the screen background colour.
	/// Note that trying to open more than one window at a time is invalid. This stems from the way SDL handles its video system, such that
	/// we can't have two different instances going at once. Because of this, trying to do so will throw an exception.
	/// Trying to update the screen in any way before opening it will also throw an exception.
	class Window
	{
	public:
		//Declare exception classes
		/// \brief Exception class for Window Initialisation exceptions
		///
		/// This exception class inherits off std::exception and provides the according "what" constructor for error summaries.
		class InitException : public std::exception
		{ 
		public:
			InitException(const char* what) : std::exception(what){};
		};
		/// \brief Exception class for invalid usage exceptions, e.g. trying to Update the screen when the window isn't open.
		///
		/// As with InitException,this inherits off std::exception and provides a "what" constructor
		class UsageException : public std::exception
		{
		public:
			UsageException(const char* what) : std::exception(what){};
		};

		//Constructor and Destructor
		//! Default Constructor. Initialises internal variables
		Window();
		//! Destructor. Closes the window if it's still open.
		~Window();

		//Declare public functions
		/// \brief Creates the OpenGL window. May throw an InitException containing the relevant error message.
		///
		/// \param title A const char* string for your title window caption.
		/// \param width The width in pixels.
		/// \param height The height in pixels.
		void Open(const char *title, int width, int height);
		//! Closes this OpenGL window.
		void Close();
		/// \brief Sets the background colour using RGB values. Will throw a UsageException if window isn't open.
		///
		/// \param r The red value, between 0 and 1.
		/// \param g The green value, between 0 and 1.
		/// \param b The blue value, between 0 and 1.
		void SetBackgroundColour(float r, float g, float b);
		//! Flips our two frame buffers to update the screen to the newly drawn frame. Will throw a UsageException if window isn't open.
		void UpdateScreen();
		//! Clears the screen in preparation for new drawing.
		void ClearScreen();

	private:
		//Declare private functions
		//This function initialises SDL Video
		void InitSDL();

		//Declare private properties
		//Whether or not we've initialised SDL, and if we have a window open or not
		bool initialised, isOpen;
		//Width/height storage
		int width, height;
	};

	/// \example Examples/ExampleWindow.cpp
	/// An example of how to use the basic Window class on its own.
	/// Note that although Windows can be used just like this it is generally not necessary as they are created automatically
	/// as part of the ProgramControl class.
}

#endif