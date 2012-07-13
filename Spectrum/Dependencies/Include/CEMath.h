/*****************************************************************
*CEngine
*Math.h by Chris Lewis
*Defines miscellaneous math functions not provided by <cmath>
*****************************************************************/

#ifndef CENGINE_MATH_H
#define CENGINE_MATH_H

#include <cmath>

//Declare C-style math functions in the CEngine::Math namespace
namespace CEngine
{
	//! Namespace for various general-purpose math functions
	namespace Math
	{
		static const float PI = 3.141592653f;

		/// \brief Template function to return the smallest of two values. Type must have operator < defined.
		///
		/// \param x The first value
		/// \param y The second value
		/// \return The smallest!
		template <class T>
		static T Min(const T& x, const T& y)
		{
			return x < y ? x : y;
		}

		/// \brief Template function to return the largest of two values. Type must have operator > defined.
		///
		/// \param x The first value
		/// \param y The second value
		/// \return The largest!
		template <class T>
		static T Max(const T& x, const T& y)
		{
			return x > y ? x : y;
		}

		/// \brief Returns the angle from point A to B, in degrees. The value will be in the range -180 to 180 inclusive, where 0 degrees
		/// indicates a direction off to the right.
		///
		/// \param a The first point.
		/// \param b The second point.
		/// \return The angle in degrees from A to B.
		static float Angle(const Vector2D& a, const Vector2D& b)
		{
			return (atan2f(b.y - a.y, b.x - a.x)*180/PI);
		}

		/// \brief Returns a vector pointing in the direction indicated by the specified angle, of the specified length.
		///
		/// \param angle The angle at which the vector should point.
		/// \param length The desired length of the vector.
		/// \return The vector pointing in that direction.
		static Vector2D AngledVector(float angle, float length)
		{
			return Vector2D(cos(angle*PI/180) * length, sin(angle*PI/180) * length);
		}
	}
}

#endif