



#ifndef CYCLONE_CORE_H
#define CYCLONE_CORE_H
#include <math.h>
#include <string>
#include "precision.h"



namespace cyclone {

	/*
	Holds a vectore in three dimension. Four data members
	are allocated to ensure alignment in an array
	*/

	class Vector3 {
	public:
		/* Holds the value of the x axis */
		real x;

		/* Holds the value of the y axis */
		real y;

		/* Holds the value of the z axis */
		real z;

	private:
		/*
			Padding to ensure four word alignment. Has not mathematical use, only to optimizer
			by having 4 floating-point values to sit better in memory
		*/
		real pad;

	public:
		/* The defult constructor creates a zero vector */
		Vector3() : x(0), y(0), z(0) {}

		/*
			The explicit constructor creates a vector
			given the components
		*/
		Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}


		/* Flip all the components of the vector. */
		void invert() {
			x = -x;
			y = -y;
			x = -z;
		}


		/** Gets the magnitude of this vector. */
		real magnitude() const
		{
			return real_sqrt(x * x + y * y + z * z);
		}


		/** Gets the squared magnitude of this vector. */
		real squareMagnitude() const
		{
			return x * x + y * y + z * z;
		}


		/** Turns a non-zero vector into a vector of unit length. */
		void normalize()
		{
			real l = magnitude();
			if (l > 0)
			{
				(*this) *= ((real)1) / l;
			}
		}


		/** Multiplies this vector by the given scalar. */
		void operator*=(const real value)
		{
			x *= value;
			y *= value;
			z *= value;
		}


		/** Returns a copy of this vector scaled the given value. */
		Vector3 operator*(const real value) const
		{
			return Vector3(x * value, y * value, z * value);
		}


		/** Adds the given vector to this. */
		void operator+=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}


		/** Returns the value of the given vector added to this. */
		Vector3 operator+(const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}


		/** Subtracts the given vector from this. */
		void operator-=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}


		/**
		* Returns the value of the given vector subtracted from this.
		*/
		Vector3 operator-(const Vector3& v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}


		/**
		* Adds the given vector to this, scaled by the given amount.
		*/
		void addScaledVector(const Vector3& vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}


		/**
		* Calculates and returns a component-wise product of this
		* vector with the given vector.
		*/
		Vector3 componentProduct(const Vector3& vector) const
		{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}
		/**
		* Performs a component-wise product with the given vector and
		* sets this vector to its result.
		*/
		void componentProductUpdate(const Vector3& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}


		/**
		* Calculates and returns the scalar product of this vector
		* with the given vector.
		*/
		real scalarProduct(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}
		/**
		* Calculates and returns the scalar product of this vector
		* with the given vector.
		*/
		real operator *(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}


		/**
		* Calculates and returns the vector product of this vector
		* with the given vector.
		*/
		Vector3 vectorProduct(const Vector3& vector) const
		{
			return Vector3(y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}
		/**
		* Updates this vector to be the vector product of its current
		* value and the given vector.
		*/
		void operator %=(const Vector3& vector)
		{
			*this = vectorProduct(vector);
		}
		/**
		* Calculates and returns the vector product of this vector
		* with the given vector.
		*/
		Vector3 operator%(const Vector3& vector) const
		{
			return Vector3(y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}


		/** Zero all the components of the vector. */
		void clear() {
			x = y = z = 0;
		}

		
		std::string print()
		{
			std::string str = "";
			str += std::to_string(x);
			str += ", ";
			str += std::to_string(y);
			str += ", ";
			str += std::to_string(z);
			str += ") ";

			return str;
		}


	};


}


#endif // CYCLONE_CORE_H