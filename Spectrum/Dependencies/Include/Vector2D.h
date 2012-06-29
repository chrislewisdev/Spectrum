/******************************************************************
*CEngine
*Vector2D.h by Chris Lewis
*Defines the Vector2D class for in-game spatial math
******************************************************************/

#ifndef CENGINE_VECTOR2D_H
#define CENGINE_VECTOR2D_H

#include <stdexcept>

namespace CEngine
{
	/// \brief Used for 2D vector storage and math.
	///
	/// The Vector2D class is a basic implementation of 2D vectors with public access for its x/y values. It supports common
	/// Vector operations like addition/subtraction, scalar multiplication/division, dot-products and so on.
	/// This should be used in most cases to represent any 2D co-ordinate.
	class Vector2D
	{
	public:
		//! Default constructor initialises x/y to 0.
		Vector2D();
		//! Constructor to initialise x/y to user-defined values.
		Vector2D(float _x, float _y);

		//Declare public functions
		/// \brief Returns the length of this vector.
		/// \return The Length of this vector
		float Length() const;
		/// \brief Returns a Unit Vector (Vector of length 1) in the same direction as this vector. 
		/// Throws an invalid_argument exception on a zero vector.
		/// \return The Unit Vector of this vector.
		Vector2D UnitVector() const;
		/// \brief Returns a Vector that is perpendicular to this one. Preserves the length of this vector.
		/// \return The perpendicular vector.
		Vector2D PerpendicularVector() const;
		/// \brief Calculates the Dot Product of this vector with another target vector.
		///
		/// \param target The target vector to calculate our Dot Product with.
		/// \return The floating-point result of the dot product.
		float DotProduct(const Vector2D& target) const;
		/// \brief Returns a vector containing only the X component of this vector.
		/// \return A vector where y=0 and x is the value from this vector.
		Vector2D XComponent() const;
		/// \brief Returns a vector containing only the Y component of this vector.
		/// \return A vector where x=0 and y is the value from this vector.
		Vector2D YComponent() const;

		//Declare operator overloads (non-member operators inlined)
		//Comparison
		friend bool operator == (const Vector2D& lhs, const Vector2D& rhs)
			{ return (lhs.x == rhs.x && lhs.y == rhs.y);}
		friend bool operator != (const Vector2D& lhs, const Vector2D& rhs)
			{return !(lhs == rhs);}
		//Vector addition/subtraction
		friend Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs)
			{ return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y); }
		Vector2D& operator += (const Vector2D& rhs);
		friend Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs)
			{ return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y); }
		Vector2D& operator -= (const Vector2D& rhs);
		//Scalar multiplication/division
		friend Vector2D operator * (float lhs, const Vector2D& rhs)
			{ return Vector2D(rhs.x * lhs, rhs.y * lhs); }
		friend Vector2D operator * (const Vector2D& lhs, float rhs)
			{ return rhs * lhs; }
		Vector2D& operator *= (float rhs);
		Vector2D operator / (float rhs) const;
		Vector2D& operator /= (float rhs);
		//Negation operator
		Vector2D operator - () const;

		//Declare public properties
		//! Horizontal displacement of this vector.
		float x;
		//!	Vertical displacement of this vector.
		float y;
	};
}

#endif