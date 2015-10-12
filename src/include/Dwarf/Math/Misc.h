#ifndef MATH_MISC_H
#define MATH_MISC_H

#include "../DwarfSetup.h"
#include "Vector2.h"

/*
Functions for general purposes
*/

namespace Dwarf
{
	namespace Math
	{

		float DWARFAPI clamp(const float &value, const float &lower, const float &upper);

		// Linearly interpolate between start - end
		float DWARFAPI lerp(const float &start, const float &end, const float &time);
		Vector2 DWARFAPI lerp(const Vector2 &start, const Vector2 &end, const float &time);

		// Spherically interpolate between start - end
		float DWARFAPI slerp(const float &start, const float &end, const float &time);

	}
}

#endif
