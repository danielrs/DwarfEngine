#include <Dwarf/Math/Vector4.h>

namespace Dwarf
{
	namespace Math
	{

		Vector4::Vector4() : super(),
			x(data[0]), y(data[1]), z(data[2]), w(data[3])
		{}

		// ----------------------------------------------------------------

		Vector4::Vector4(const Vector4 &b) : super(b),
			x(data[0]), y(data[1]), z(data[2]), w(data[3])
		{}

		// ----------------------------------------------------------------

		Vector4::Vector4(const VectorN<float, 4> &b) : super(b),
			x(data[0]), y(data[1]), z(data[2]), w(data[3])
		{}

		// ----------------------------------------------------------------

		Vector4::Vector4(const float &x, const float &y, const float &z, const float &w) :
			x(data[0]), y(data[1]), z(data[2]), w(data[3])
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		// ================================================================
		//	Operators
		// ================================================================

		Vector4& Vector4::operator = (const Vector4 &b)
		{
			copy(b);

			return *this;
		}

	} // end of namespace Math
} // end of namespace Dwarf
