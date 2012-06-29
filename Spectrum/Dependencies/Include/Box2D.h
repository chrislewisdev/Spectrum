/**********************************************************
*CEngine
*Box2D.h by Chris Lewis
*Declaration for Box2D struct
*Stores point/size data and processes square collisions
**********************************************************/

#ifndef CENGINE_BOX2D_H
#define CENGINE_BOX2D_H

//Include necessary headers
#include "Vector2D.h"

//Declare class inside the CEngine namespace
namespace CEngine
{
	/// \brief Structure for containing 2D rectangle data- position/size as well as collision calculations.
	///
	/// All-public class with position ('pos') and size ('size) members, along with overloaded constructors for initialisation.
	/// This class also contains methods to test for Box Collisions with Points and other Boxes
	struct Box2D
	{
		//! Default constructor, will initialise position/size to (0,0) each
		Box2D();
		//! Constructor to take explicit position/size structs for initialisation
		Box2D(Vector2D p, Vector2D s);
		//! Constructor to take individual float values for position then size
		Box2D(float x, float y, float xSize, float ySize);

		//Declare public functions
		/// \brief Checks if the target Vector Position is within our box
		///
		/// \param target The target position to check against
		/// \return True if there's a collision, false if not
		bool Contains(Vector2D target) const;
		/// \brief Checks if the target box is entirely contained within this box
		///
		/// \param target The box to check against
		/// \return True if the target box is completely contained within this box, false if not
		bool Contains(const Box2D& target) const;
		/// \brief Checks for collision against a Vector Position with a size- if the target area overlaps with our Box
		///
		/// \param target The target position to check against
		/// \param targetSize The width/height values of the target area
		/// \return True if there's a collision, false if not
		bool Overlap(Vector2D target, Vector2D targetSize) const;
		/// \brief Checks for collision against another Box- if the two Boxes overlap at all
		///
		/// \param target The target Box to check against
		/// \return True if there's a collision, false if not
		bool Overlap(const Box2D& target) const;

		//Declare public properties
		//! Position (x,y) info
		Vector2D pos;
		//! Size (x,y) info
		Vector2D size;
	};

	/// \example Examples/ExampleBox2D.cpp
	/// Demonstrates usage of the Box2D class visually with collision and positioning.
}

#endif