#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "../DwarfSetup.h"
#include "Def.h"
#include "MatrixNxN.h"
#include "VectorN.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cmath>

// ================================================================
//	Declaration
// ================================================================

namespace Dwarf
{
	namespace Math
	{

		template <typename T>
		class DWARFAPI Matrix4x4 : public MatrixNxN<T, 4, 4>
		{
		private:
			typedef MatrixNxN<T, 4, 4> super;
		public:
			Matrix4x4();
			Matrix4x4(const T &value);
			Matrix4x4(const MatrixNxN<T, 4, 4> &b);

			// Transform functions
			static Matrix4x4 identity();
			static Matrix4x4 translate(const T &x, const T &y, const T &z);
			static Matrix4x4 translate(const VectorN<T, 3> &dir);
			static Matrix4x4 translate(const VectorN<T,2> &dir, const T &z);
			static Matrix4x4 translate(const VectorN<T,2> &dir);
			static Matrix4x4 scale(const T &x, const T &y, const T &z);
			static Matrix4x4 scale(const T &xyz);
			static Matrix4x4 rotate(const T &angle, const VectorN<T, 3> &axis);
			static Matrix4x4 rotate(const T &angle, const T &x, const T &y, const T &z);
			static Matrix4x4 rotate(const T &angleX, const T &angleY, const T &angleZ);
			static Matrix4x4 rotate(const T &angle);

			// Basis transform functions
			static Matrix4x4 lookAt(const VectorN<T, 3> &eye, const VectorN<T, 3> &center, const VectorN<T, 3> &up);
			static Matrix4x4 frustum(const T &left, const T &right, const T &top, const T &bottom, const T &near, const T &far);
			static Matrix4x4 perspective(const T &fov, const T &aspect, const T &near, const T &far);
			static Matrix4x4 ortho(const T &left, const T &right, const T &bottom, const T &top, const T &near, const T &far);

			// Operators
			Matrix4x4 operator * (const Matrix4x4 &b) const;
			Vector3 operator * (const Vector3 &b) const;
			Vector2 operator * (const Vector2 &b) const;
		};
		using Matrix4 = Matrix4x4<float>;
	}
}

// ================================================================
//	Definition
// ================================================================

namespace Dwarf
{
	namespace Math
	{

		template <typename T>
		Matrix4x4<T>::Matrix4x4() : super()
		{
			// Sets last element to 1
			this->data[this->height - 1][this->width - 1] = 1;
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T>::Matrix4x4(const T &value) : super()
		{
			// Sets diagonal to value
			for (int n = 0, m = 0; n < this->height && m < this->width; ++n, ++m)
				this->data[n][m] =  value;
		}

		// --------------------------------

		template <typename T>
		Matrix4x4<T>::Matrix4x4(const MatrixNxN<T, 4, 4> &b) : super(b) {}

		// ================================================================
		//	Transformations
		// ================================================================

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::identity()
		{
			Matrix4x4 matrix;

			// Traverse diagonals
			for (int n = 0, m = 0; n < MatrixNxN<T, 4, 4>::height && m < MatrixNxN<T, 4, 4>::width; ++n, ++m)
				matrix[n][m] = 1;

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::translate(const T &x, const T &y, const T &z)
		{
			Matrix4x4 matrix = identity();

			// Sets right-most element of each row
			matrix[0][3] = x;
			matrix[1][3] = y;
			matrix[2][3] = z;

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::translate(const VectorN<T, 3> &dir)
		{
			return translate(dir[0], dir[1], dir[2]);
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::translate(const VectorN<T, 2> &dir, const T& z)
		{
			return translate(dir[0], dir[1], z);
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::translate(const VectorN<T, 2> &dir)
		{
			return translate(dir[0], dir[1], 0);
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::scale(const T &x, const T &y, const T &z)
		{
			Matrix4x4 matrix;

			// Sets the diagonal elements
			matrix[0][0] = x;
			matrix[1][1] = y;
			matrix[2][2] = z;

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::scale(const T &xyz)
		{
			return scale(xyz, xyz, xyz);
		}

		// ----------------------------------------------------------------
		// see: http://en.wikipedia.org/wiki/Rotation_matrix

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::rotate(const T &angle, const VectorN<T, 3> &axis)
		{
			Matrix4x4 matrix;

			// Normalizes axis
			const VectorN<T, 3> unitVec = axis.normalized();

			// Values used in matrix generation
			const T x = unitVec[0];
			const T y = unitVec[1];
			const T z = unitVec[2];
			const T xx = x*x;
			const T xy = x*y;
			const T xz = x*z;
			const T yy = y*y;
			const T yz = y*z;
			const T zz = z*z;

			// Converts angle to radians
			const double radians = angle / 180.0f * PI;

			const T sinAngle = static_cast<T>(sin(radians));
			const T cosAngle = static_cast<T>(cos(radians));
			const T oneMinusCos = 1 - cosAngle;

			// First row
			matrix[0][0] = cosAngle + xx*oneMinusCos;
			matrix[0][1] = xy*oneMinusCos - z*sinAngle;
			matrix[0][2] = xz*oneMinusCos + y*sinAngle;
			// Second row
			matrix[1][0] = xy*oneMinusCos + z*sinAngle;
			matrix[1][1] = cosAngle + yy*oneMinusCos;
			matrix[1][2] = yz*oneMinusCos - x*sinAngle;
			// Third row
			matrix[2][0] = xz*oneMinusCos - y*sinAngle;
			matrix[2][1] = yz*oneMinusCos + x*sinAngle;
			matrix[2][2] = cosAngle + zz*oneMinusCos;

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::rotate(const T &angle, const T &x, const T &y, const T &z)
		{
			return rotate(angle, Vector3(x, y, z));
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::rotate(const T &angleX, const T &angleY, const T &angleZ)
		{
			return	rotate(angleZ, Vector3(0, 0, 1)) *
					rotate(angleY, Vector3(0, 1, 0)) *
					rotate(angleX, Vector3(1, 0, 0));
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::rotate(const T &angle)
		{
			return rotate(angle, Vector3(0, 0, 1));
		}

		// ================================================================
		//	Basis transforms
		// ================================================================

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::lookAt(const VectorN<T, 3> &eye, const VectorN<T, 3> &center, const VectorN<T, 3> &up)
		{
			VectorN<T, 3> upN = up.normalized();
			VectorN<T, 3> forward = (eye - center).normalize();
			VectorN<T, 3> side = Vector3::cross(upN, forward);
			VectorN<T, 3> newUp = Vector3::cross(forward, side);

			Matrix4x4 matrix;

			matrix[0][0] = side[0];		matrix[0][1] = side[1];		matrix[0][2] = side[2];		matrix[0][3] = -Vector3::dot(side, eye);
			matrix[1][0] = newUp[0];	matrix[1][1] = newUp[1];	matrix[1][2] = newUp[2];	matrix[1][3] = -Vector3::dot(newUp, eye);
			matrix[2][0] = forward[0];	matrix[2][1] = forward[1];	matrix[2][2] = forward[2];	matrix[2][3] = -Vector3::dot(forward, eye);

			return matrix;
		}

		// ----------------------------------------------------------------

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::frustum(const T &left, const T &right, const T &top, const T &bottom, const T &near, const T &far)
		{
			Matrix4x4 matrix = identity();

			if ((left == right) || (top == bottom) || (near == far) ||
				(near < 0) || (far < 0)) return matrix;

			// First row
			matrix[0][0] = (2 * near) / (right - left);
			matrix[0][2] = (right + left) / (right - left);
			// Second row
			matrix[1][1] = (2 * near) / (top - bottom);
			matrix[1][2] = (top + bottom) / (top - bottom);
			// Third row
			matrix[2][2] = (near + far) / (near - far);
			matrix[2][3] = (2 * near * far) / (near - far);
			// Fourth row
			matrix[3][2] = -1;

			return matrix;
		}

		// ----------------------------------------------------------------
		// See: http://www.songho.ca/opengl/gl_projectionmatrix.html#perspective

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::perspective(const T &fovy, const T &aspect, const T &near, const T &far)
		{
			T q = 1 / tan((0.5f * fovy) / 180 * PI);
			T A = q / aspect;
			T B = (near + far) / (near - far);
			T C = (2.0f * near * far) / (near - far);

			Matrix4x4 matrix;

			matrix[0] = Vector4(A, 0, 0, 0);
			matrix[1] = Vector4(0, q, 0, 0);
			matrix[2] = Vector4(0, 0, B, C);
			matrix[3] = Vector4(0, 0, -1, 0);

			return matrix;
		}

		// ----------------------------------------------------------------
		// See: http://www.songho.ca/opengl/gl_projectionmatrix.html#ortho

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::ortho(const T &left, const T &right, const T &bottom, const T &top, const T &near, const T &far)
		{
			Matrix4x4 matrix;

			if ((left == right) || (top == bottom) || (near == far) ||
				(near < 0) || (far < 0)) return matrix;

			matrix[0] = Vector4(2 / (right - left), 0, 0, (left + right) / (left - right));
			matrix[1] = Vector4(0, 2 / (top - bottom), 0, (bottom + top) / (bottom - top));
			matrix[2] = Vector4(0, 0, 2 / (near - far), (near + far) / (near - far));
			matrix[3] = Vector4(0, 0, 0, 1);

			return matrix;
		}

		// ================================================================
		//	Operators
		// ================================================================

		template <typename T>
		Matrix4x4<T> Matrix4x4<T>::operator * (const Matrix4x4 &b) const
		{
			return super::operator*(b);
		}

		// ----------------------------------------------------------------

		template <typename T>
		Vector3 Matrix4x4<T>::operator * (const Vector3 &b) const
		{
			Vector3 vector;

			for (int i = 0; i < 3; i++)
				vector[i] = this->data[i][0] * b[0] + this->data[i][1] * b[1] + this->data[i][2] * b[2] + this->data[i][3] * b.w;

			return vector;
		}

		// --------------------------------

		template <typename T>
		Vector2 Matrix4x4<T>::operator * (const Vector2 &b) const
		{
			Vector2 vector;

			for (int i = 0; i < 2; ++i)
				vector[i] = this->data[i][0] * b[0] + this->data[i][1] * b[1] + this->data[i][3] * b.w;

			return vector;
		}

	} // end of namespace Math
} // end of namespace Dwarf

#endif
