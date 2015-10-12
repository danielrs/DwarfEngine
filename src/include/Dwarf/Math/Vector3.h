#ifndef VECTOR3_H
#define VECTOR3_H

#include "../DwarfSetup.h"
#include "Def.h"
#include "VectorN.h"

namespace Dwarf
{
	namespace Math
	{

		class DWARFAPI Vector3 : public VectorN<float, 3>
		{
		private:
			typedef VectorN<float, 3> super;
		public:
			union
			{
				struct { float &x, &y, &z; };
				struct { float &r, &g, &b; };
			};

			bool w;

			Vector3();
			Vector3(const Vector3 &b);
			Vector3(const VectorN<float, 3> &b);
			Vector3(const float &x, const float &y, const float &z);

			static Vector3 cross(const Vector3 &a, const Vector3& b);

			// Operator
			Vector3& operator = (const Vector3 &b);

		};
		using Vec3 = Vector3;

		DECLARE_DIV_MUL_OPERATORS(Vector3, float);

	}
}
#endif
