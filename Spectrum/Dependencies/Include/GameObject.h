/*********************************************************************
*CEngine
*GameObject.h by Chris Lewis
*Declares the Game Object class, a base class for all in-game objects to inherit off
*********************************************************************/

#ifndef CENGINE_GAMEOBJECT_H
#define CENGINE_GAMEOBJECT_H

#include "Box2D.h"

namespace CEngine
{
	/// \brief Class to use as a base class for all in-game objects.
	///
	/// The GameObject class provides virtual functions and basic members that are to be present in every type of Game Object you use
	/// in your game. These functions are namely Update() and Draw() functions, which can be called to perform your main game logic
	/// and graphics drawing for any singular object. The main property is a Box2D which is used for specifying the bounding box of an object,
	/// along with a corresponding get function for this property.
	/// This class will include Lua scripting integration functionality when I get to it.
	class GameObject
	{
	public:
		//! Basic constructor initialises everything to 0 (or equivalent values)
		GameObject();
		//! Constructor to initialise the position/size of our object
		GameObject(Box2D boundingBox);
		//! Virtual Destructor to support polymorphism
		virtual ~GameObject() {}

		//Declare public functions
		/// \brief Performs a single Update loop on our GameObject, performing all necessary logic. Override this function to provide
		/// your primary object behaviour for an object type.
		///
		/// \param deltaTime The time that has passed in seconds since the last update.
		/// \return void
		virtual void Update(float deltaTime);
		/// \brief Draws our object to the screen. Override this function to specify how your object will be drawn.
		///
		/// \return void
		virtual void Draw();
		/// \brief Virtual function return a newly constructed (dynamic) copy of this GameObject instance. While useful in a general sense
		/// this function is also utilised by CEngine's internals for polymorphic copying of GameObjects so this is an important function
		/// to keep implemented in your child classes!
		///
		/// \return A new dynamically constructed GameObject, as a copy of this one.
		virtual GameObject *Clone() const;
		/// \brief Returns a copy of this object's bounding box.
		///
		/// \return A value copy our bounding box.
		Box2D BoundingBox();

	protected:
		//Declare protected functions
		/// \brief Draws our bounding box as a square in the screen position corresponding to its position/size.
		/// No colour is specified so you may specify it (and other changes) yourself before calling the draw.
		///
		/// \return void.
		void DrawBoundingBox();

		//Declare protected properties
		//Bounding box storage
		Box2D bounds;
	};
}

#endif