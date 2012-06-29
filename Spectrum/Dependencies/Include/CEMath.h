/*****************************************************************
*CEngine
*Math.h by Chris Lewis
*Defines miscellaneous math functions not provided by <cmath>
*****************************************************************/

#ifndef CENGINE_MATH_H
#define CENGINE_MATH_H

//Declare C-style functions in the CEngine::Math namespace
namespace CEngine
{
	//! Namespace for various general-purpose math functions
	namespace Math
	{
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
	}
}

#endif