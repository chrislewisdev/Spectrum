/*****************************************************************
*CEngine
*Collision.h by Chris Lewis
*Declares functions in the Collision namespace for collision checks between differing geometric classes
*****************************************************************/

#ifndef CENGINE_COLLISION_H
#define CENGINE_COLLISION_H

#include "Box2D.h"
#include "Circle2D.h"
#include "Ray2D.h"

namespace CEngine
{
	//! Contains functions to check for collisions between differing geometry classes, like Box2D/Ray2D/Circle2D
	namespace Collision
	{
		/// \brief Checks for and returns an intersection point between Ray2D and Box2D. Returns constant Collision::NoIntersection
		/// if they do not intersect.
		///
		/// \param ray The Ray2D to use in the check.
		/// \param box The Box2D to use in the check.
		/// \return The point of intersection, or Collision::NoIntersection if there is none.
		Vector2D RayBoxIntersection(const Ray2D& ray, const Box2D& box);
		/// \brief Checks for and returns an intersection point between Ray2D and Circle2D. Returns constant Collision::NoIntersection
		/// if they do not intersect.
		///
		/// \param ray The Ray2D to use in the check.
		/// \param circle The Circle2D to use in the check.
		/// \return The point of intersection, or Collision::NoIntersection if there is none.
		Vector2D RayCircleIntersection(const Ray2D& ray, const Circle2D& circle);
		/// \brief Checks for an overlapping collision between a Circle2D and Box2D.
		///
		/// \param circle The Circle2D to use in the check.
		/// \param box The Box2D to use in the check.
		/// \return True if they overlap, false if not.
		bool CircleBoxOverlap(const Circle2D& circle, const Box2D& box);

		//! Constant used to indicate a non-existent intersection point between two objects
		extern const Vector2D NoIntersection;
	}
}

#endif