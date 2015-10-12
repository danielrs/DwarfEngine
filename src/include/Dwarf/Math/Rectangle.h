#ifndef DWARF_MATH_RECTANGLE_H
#define DWARF_MATH_RECTANGLE_H

#include "../DwarfSetup.h"
#include "Vector2.h"

namespace Dwarf {
	namespace Math {

		struct DWARFAPI Rectangle {
			Vector2 position;
			Vector2 size;

			Rectangle();
			Rectangle(const Vector2 &rect, const Vector2 &size);
			Rectangle(const float &x, const float &y, const float &width, const float &height);
		};
	}
}
#endif
