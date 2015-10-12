#ifndef VECTOR4_H
#define VECTOR4_H

#include "../DwarfSetup.h"
#include "Def.h"
#include "VectorN.h"

namespace Dwarf
{
	namespace Math
	{

		class DWARFAPI Vector4 : public VectorN<float, 4>
		{
		private:
			typedef VectorN<float, 4> super;
		public:
			union
			{
				struct { float &x, &y, &z, &w; };
				struct { float &r, &g, &b, &a; };
			};

			Vector4();
			Vector4(const Vector4 &b);
			Vector4(const VectorN<float, 4> &b);
			Vector4(const float &x, const float &y, const float &z, const float &w);

			// Operator
			Vector4& operator = (const Vector4 &b);
		};
		using Vec4 = Vector4;

		DECLARE_DIV_MUL_OPERATORS(Vector4, float);

	}
}
#endif
