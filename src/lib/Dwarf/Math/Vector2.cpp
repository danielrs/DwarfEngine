#include <Dwarf/Math/Vector2.h>
#include <cmath>
#include <cstring>

namespace Dwarf
{
	namespace Math
	{

		Vector2::Vector2() : super(),
			x(data[0]), y(data[1])
		{
			w = 1;
		}

		// ----------------------------------------------------------------

		Vector2::Vector2(const Vector2& b) : super(b),
			x(data[0]), y(data[1])
		{
			w = b.w;
		}

		// ----------------------------------------------------------------

		Vector2::Vector2(const VectorN<float, 2> &b) : super(b),
			x(data[0]), y(data[1])
		{
			w = 1;
		}

		// ----------------------------------------------------------------

		Vector2::Vector2(const float &x, const float &y) :
			x(data[0]), y(data[1])
		{
			this->x = x;
			this->y = y;
			w = 1;
		}

		// ----------------------------------------------------------------

		float Vector2::cross(const Vector2 &a, const Vector2 &b)
		{
			return (a[0] * b[1] - b[0] * a[1]);
		}

		// ================================================================
		//	Operators
		// ================================================================

		Vector2& Vector2::operator = (const Vector2 &b)
		{
			copy(b);
			w = b.w;

			return *this;
		}

	} // end of namespace Math
} // end of namespace Dwarf
