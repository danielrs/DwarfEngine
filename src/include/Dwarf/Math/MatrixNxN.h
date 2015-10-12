#ifndef MATRIXNX_H
#define MATRIXNX_H

#include <ostream>

#include "../DwarfSetup.h"
#include "VectorN.h"

#include <stdexcept>

// ================================================================
//	Declaration
// ================================================================

namespace Dwarf
{
	namespace Math
	{

		template <typename T, int H, int W>
		class DWARFAPI MatrixNxN
		{
		private:
			// Memory for the flat array
			T m_flat[H * W];
			void copy(const MatrixNxN &b);
		public:
			const static int width = W;
			const static int height = H;

			VectorN<T, W> data[H];

			// Methods
			MatrixNxN<T, W, H> transposed();

			// Assignment operator
			MatrixNxN& operator = (const MatrixNxN &b);

			// Subscript operator
			VectorN<T, W>& operator [] (const int &index);
			const VectorN<T, W>& operator [] (const int &index) const;

			// Arithmetic operators
			MatrixNxN operator + (const MatrixNxN &b) const;
			MatrixNxN operator - (const MatrixNxN &b) const;
			MatrixNxN operator * (const MatrixNxN &b) const;
			VectorN<T, H> operator * (const VectorN<T, W> &b) const;
			MatrixNxN operator * (const T &b) const;

			// Arithmetic assignment operators
			MatrixNxN& operator += (const MatrixNxN &b);
			MatrixNxN& operator -= (const MatrixNxN &b);
			MatrixNxN& operator *= (const MatrixNxN &b);
			MatrixNxN& operator *= (const T &b);

			// Access operators
			operator T * ();
			operator const T * () const;

		};

	}
}

// ================================================================
//	Definition
// ================================================================

namespace Dwarf
{
	namespace Math
	{

		template <typename T, int H, int W>
		void MatrixNxN<T, H, W>::copy(const MatrixNxN &b)
		{
			for (int i = 0; i < H; ++i)
				data[i] = b[i];
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, W, H> MatrixNxN<T, H, W>::transposed()
		{
			// Transposed matrix
			MatrixNxN<T, W, H> matrix;

			for (int m = 0; m < W; ++m)
			{
				VectorN<T, H> row;

				for (int n = 0; n < H; ++n)
				{
					row[n] = data[n][m];
				}

				matrix[m] = row;
			}

			return matrix;
		}

		// ================================================================
		//	Operators
		// ================================================================

		template <typename T, int H, int W>
		MatrixNxN<T, H, W>& MatrixNxN<T, H, W>::operator = (const MatrixNxN& b)
		{
			copy(b);
			return *this;
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		VectorN<T, W>& MatrixNxN<T, H, W>::operator [] (const int &index)
		{
			if (index < 0 || index >= H)
				throw std::out_of_range("Index out of bounds");

			return data[index];
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		const VectorN<T, W>& MatrixNxN<T, H, W>::operator [] (const int &index) const
		{
			if (index < 0 || index >= H)
				throw std::out_of_range("Index out of bounds");

			return data[index];
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W> MatrixNxN<T, H, W>::operator + (const MatrixNxN &b) const
		{
			MatrixNxN result;
			for (int i = 0; i < H; ++i)
				result[i] = data[i] + b[i];

			return result;
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W> MatrixNxN<T, H, W>::operator - (const MatrixNxN &b) const
		{
			MatrixNxN matrix;
			for (int i = 0; i < H; ++i)
				matrix[i] = data[i] - b[i];

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W> MatrixNxN<T, H, W>::operator * (const MatrixNxN &b) const
		{
			// Size of result matrix
			MatrixNxN<T, H, W> matrix;

			// Begins to traverse this
			for (int n = 0; n < height; ++n)
			{
				// Begins to traverse b
				for (int bm = 0; bm < b.width; ++bm)
				{
					T sum(0);

					for (int m = 0; m < width; ++m)
						sum += data[n][m] * b[m][bm];

					matrix[n][bm] = sum;
				}
			}

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		VectorN<T, H> MatrixNxN<T, H, W>::operator * (const VectorN<T, W> &b) const
		{
			VectorN<T, H> vector;

			for (int n = 0; n < height; ++n)
			{
				T sum(0);

				for (int m = 0; m < width; ++m)
					sum += data[n][m] * b[m];

				vector[n] = sum;
			}

			return vector;
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W> MatrixNxN<T, H, W>::operator * (const T &b) const
		{
			MatrixNxN matrix;
			for (int i = 0; i < H; ++i)
				matrix[i] = data[i] * b;

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W>& MatrixNxN<T, H, W>::operator += (const MatrixNxN &b)
		{
			return (*this = *this + b);
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W>& MatrixNxN<T, H, W>::operator -= (const MatrixNxN &b)
		{
			return (*this = *this - b);
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W>& MatrixNxN<T, H, W>::operator *= (const MatrixNxN &b)
		{
			return (*this = *this * b);
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W>& MatrixNxN<T, H, W>::operator *= (const T &b)
		{
			return (*this = *this * b);
		}

		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		MatrixNxN<T, H, W>::operator T* ()
		{
			return &data[0][0];
		}

		template <typename T, int H, int W>
		MatrixNxN<T, H, W>::operator const T* () const
		{
			return &data[0][0];
		}


		// ----------------------------------------------------------------

		template <typename T, int H, int W>
		std::ostream& operator << (std::ostream &a, const MatrixNxN<T, H, W> &b) {

			for (int n = 0; n < H; ++n)
			{
				for (int m = 0; m < W; ++m)
				{
					a << b[n][m];
					if (m + 1 < W)
						a << ", ";
				}
				a << std::endl;
			}

			return a;
		}

	} // end of namespace Math
} // end of namespace Dwarf

#endif
