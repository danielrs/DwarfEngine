#include <Dwarf/Math/Vector3.h>
#include <cmath>

namespace Dwarf
{
	namespace Math
	{
		Vector3::Vector3() : super(),
			x(super::data[0]), y(super::data[1]), z(super::data[2])
		{
			w = 1;
		}

		// ----------------------------------------------------------------

		Vector3::Vector3(const Vector3& b) : super(b),
			x(super::data[0]), y(super::data[1]), z(super::data[2])
		{
			w = b.w;
		}

		// ----------------------------------------------------------------

		Vector3::Vector3(const VectorN<float, 3> &b) : super(b),
			x(super::data[0]), y(super::data[1]), z(super::data[2])
		{
			w = 1;
		}

		// ----------------------------------------------------------------

		Vector3::Vector3(const float &x, const float &y, const float &z) :
			x(super::data[0]), y(super::data[1]), z(super::data[2])
		{
			this->x = x;
			this->y = y;
			this->z = z;
			w = 1;
		}

		// ----------------------------------------------------------------

		Vector3 Vector3::cross(const Vector3 &a, const Vector3 &b)
		{
			return Vector3(	a[1]*b[2] - b[1]*a[2],
							a[2]*b[0] - b[2]*a[0],
							a[0]*b[1] - b[0]*a[1]);
		}

		// ================================================================
		//	Operators
		// ================================================================

		Vector3& Vector3::operator = (const Vector3 &b)
		{
			copy(b);
			w = b.w;

			return *this;
		}
	}
}
