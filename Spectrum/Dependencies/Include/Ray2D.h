/*********************************************************************
*CEngine
*Ray2D.h by Chris Lewis
*Defines a basic implementation of Rays for raycasting and other operations
*********************************************************************/

#ifndef CENGINE_RAY2D_H
#define CENGINE_RAY2D_H

#include "Vector2D.h"

namespace CEngine
{
	/// \brief Used for Raycasting and related space/collision data.
	///
	/// The Ray2D class is a relatively simple implementation of Rays using Vectors to represent its Origin and Direction. This is primarily
	/// designed to be used in collisions against other shapes like AABBs (the Box2D class) and, of course, other Rays.
	/// Note that when you create a ray, the Direction vector denotes the length of the ray as well as the direction.
	class Ray2D
	{
	public:
		//! Main Constructor. Must initialise both origin and direction of Ray.
		Ray2D(Vector2D o, Vector2D d);

		//Declare public functions
		/// \brief Checks if the target point lies on this ray.
		/// \return True if the point lies on this ray, false if not.
		bool Contains(const Vector2D& target) const;
		/// \brief Checks for intersection against the target Ray and returns the point of intersection. If they don't intersect, throws
		/// an exception.
		///
		/// \param target The ray to check for intersection with.
		/// \return The point of intersection- if no intersection, returns the static const member Ray2D::NoIntersection.
		Vector2D IntersectionPoint(const Ray2D& target) const;
		/// \brief Convenience function to check if two rays intersect without returning an intersection point.
		/// \return True if they intersect, false if not.
		bool Intersects(const Ray2D& target) const;

		//Declare public properties
		//! Vector dictating our origin position
		Vector2D origin;
		//! Vector dictating our Ray direction
		Vector2D direction;

		//! Declare a constant point used to indicate a non-existent intersection point between rays
		static const Vector2D NoIntersection;
	};
}

#endif