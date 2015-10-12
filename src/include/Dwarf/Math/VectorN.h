#ifndef VECTORN_H
#define VECTORN_H

#include "../DwarfSetup.h"
#include "Def.h"

#include <cmath>
#include <stdexcept>

// ================================================================
//	Template declaration
// ================================================================

namespace Dwarf
{
	namespace Math
	{
		template <typename T, int N>
		class DWARFAPI VectorN
		{
		protected:
			void copy(const VectorN &b);

		public:
			const static int LENGTH = N;
			mutable T data[N];

			VectorN();
			VectorN(const T &val);

			// Methods
			T magnitude() const;
			T magnitudeSquared() const;
			VectorN& normalize();
			VectorN normalized() const;
			void scaleTo(T magnitude);

			// Static Methods
			static T distance(const VectorN &a, const VectorN &b);
			static T distanceSquared(const VectorN &a, const VectorN &b);
			static T dot(const VectorN &a, const VectorN &b);
			/*
			The cross product is different depending on child class
			it should be implemented there.
			*/

			// Assignment operator
			VectorN& operator = (const VectorN &b);

			// Arithmetic operators
			T& operator [] (const int &index);
			const T& operator [] (const int &index) const;
			VectorN operator - () const;
			VectorN operator - (const VectorN &b) const;
			VectorN operator + (const VectorN &b) const;
			VectorN operator * (const T &b) const;
			VectorN operator / (const T &b) const;


			// Arithmetic assignment operators
			VectorN& operator -= (const VectorN &b);
			VectorN& operator += (const VectorN &b);
			VectorN& operator /= (const T &b);
			VectorN& operator *= (const T &b);

		};

	} // end of namespace Math
} // end of namespace Math

// ================================================================
//	Template definition
// ================================================================

namespace Dwarf
{
	namespace Math
	{

		template <typename T, int N>
		VectorN<T, N>::VectorN()
		{
			for (int i = 0; i < N; ++i)
				data[i] = 0;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N>::VectorN(const T &val)
		{
			for (int i = 0; i < N; ++i)
				data[i] = val;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		void VectorN<T, N>::copy(const VectorN &b)
		{
			for (int i = 0; i < N; ++i)
				data[i] = b[i];
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		T VectorN<T, N>::magnitude() const
		{
			return sqrt(magnitudeSquared());
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		T VectorN<T, N>::magnitudeSquared() const
		{
			T sum = 0;
			for (int i = 0; i < N; ++i)
				sum += data[i] * data[i];
			return sum;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N>& VectorN<T, N>::normalize()
		{
			T mag = magnitude();
			*this /= mag;
			return static_cast<VectorN&>(*this);
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N> VectorN<T, N>::normalized() const
		{
			// VectorNreates a vector of the same type and length
			// and copies values
			VectorN normalized;
			for (int i = 0; i < N; ++i)
				normalized[i] = data[i];

			return normalized.normalize();
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		void VectorN<T, N>::scaleTo(T magnitude)
		{
			normalize();
			*this *= magnitude;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		T VectorN<T, N>::distance(const VectorN &a, const VectorN &b)
		{
			VectorN relative = b - a;
			return relative.magnitude();
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		T VectorN<T, N>::distanceSquared(const VectorN &a, const VectorN &b)
		{
			VectorN relative = b - a;
			return relative.magnitudeSquared();
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		T VectorN<T, N>::dot(const VectorN &a, const VectorN &b)
		{
			T dot(0);
			for (int i = 0; i < N; ++i)
				dot += a[i] * b[i];

			return dot;
		}

		// ================================================================
		//	Operators
		// ================================================================

		template <typename T, int N>
		VectorN<T, N>& VectorN<T, N>::operator = (const VectorN &b)
		{
			copy(b);
			return *this;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		T& VectorN<T, N>::operator [] (const int &index)
		{
			if (index < 0 || index >= LENGTH)
				throw std::out_of_range("Index out of bounds!");

			return data[index];
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		const T& VectorN<T, N>::operator [] (const int &index) const
		{
			if (index < 0 || index >= LENGTH)
				throw std::out_of_range("Index out of bounds!");

			return data[index];
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N> VectorN<T, N>::operator - () const
		{
			VectorN vector;
			for (int i = 0; i < N; ++i)
				vector[i] = -data[i];
			return vector;
		}

		template <typename T, int N>
		VectorN<T, N> VectorN<T, N>::operator - (const VectorN &b) const
		{
			VectorN vector;
			for (int i = 0; i < N; i++)
				vector[i] = data[i] - b[i];
			return vector;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N> VectorN<T, N>::operator + (const VectorN &b) const
		{
			VectorN vector;
			for (int i = 0; i < N; ++i)
				vector[i] = data[i] + b[i];
			return vector;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N> VectorN<T, N>::operator * (const T &b) const
		{
			VectorN vector;
			for (int i = 0; i < N; ++i)
				vector[i] = data[i] * b;
			return vector;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N> VectorN<T, N>::operator / (const T &b) const
		{
			VectorN vector;
			for (int i = 0; i < N; ++i)
				vector[i] = data[i] / b;
			return vector;
		}

		// ================================================================
		//	Arithmetic assignment operators
		// ================================================================

		template <typename T, int N>
		VectorN<T, N>& VectorN<T, N>::operator -= (const VectorN &b)
		{
			return *this = *this - b;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N>& VectorN<T, N>::operator += (const VectorN &b)
		{
			return *this = *this + b;
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N>& VectorN<T, N>::operator /= (const T &b)
		{
			return static_cast<VectorN&>(*this = *this / b);
		}

		// ----------------------------------------------------------------

		template <typename T, int N>
		VectorN<T, N>& VectorN<T, N>::operator *= (const T &b)
		{
			return *this = *this * b;
		}

	} // end of namespace Math
} // end of namespace Dwarf

#endif
