#ifndef DWARF_MATH_VECTOR2_H
#define DWARF_MATH_VECTOR2_H

#include "../DwarfSetup.h"
#include "Def.h"
#include "VectorN.h"

namespace Dwarf
{
	namespace Math
	{

		class DWARFAPI Vector2 : public VectorN<float, 2>
		{
		private:
			typedef VectorN<float, 2> super;
		public:
			union
			{
				struct { float &x, &y; };
			};

			bool w;

			Vector2();
			Vector2(const Vector2& b);
			Vector2(const VectorN<float, 2> &b);
			Vector2(const float &x, const float &y);

			static float cross(const Vector2 &a, const Vector2 &b);

			// Operators
			Vector2& operator = (const Vector2 &b);
		};
		using Vec2 = Vector2;

		DECLARE_DIV_MUL_OPERATORS(Vector2, float);
	}
}


#endif
