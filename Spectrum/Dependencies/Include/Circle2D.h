/*******************************************************************
*CEngine
*Circle2D.h by Chris Lewis
*Defines a basic circle class for spatial information and collision handling
*******************************************************************/

#ifndef CENGINE_CIRCLE2D_H
#define CENGINE_CIRCLE2D_H

#include "Vector2D.h"

namespace CEngine
{
	/// \brief Provides an all-public implementation of a 2D Circle with collision functions.
	///
	/// The Circle2D class contains all information required to specify a circle on the screen- that is, a point dictating its center
	/// and a float value dictating its radius. It has functions which can be used to easily check for overlaps with other circles and,
	/// via the CEngine::Collision namespace, can be used to check for collisions with other types of geometry as well (such as Box2D and Ray2D).
	class Circle2D
	{
	public:
		//! Default constructor, initialises everything to 0
		Circle2D();
		//! Constructor to initialise our circle properties
		Circle2D(Vector2D p, float r);

		//Declare public functions
		/// \brief Checks to see if the target point lies within this circle.
		///
		/// \param target The target point to check against.
		/// \return True if if the point is inside our circle, false if not.
		bool Contains(Vector2D target) const;
		/// \brief Checks to see if the target circle overlaps with this one.
		///
		/// \param target The target circle to check against
		/// \return True if the circle overlaps with this, false if not.
		bool Overlap(const Circle2D& target) const;

		//Declare public properties
		//! Position indicator for the center of our circle.
		Vector2D pos;
		//! The radius of our circle moving out from the center.
		float radius;
	};
}

#endif