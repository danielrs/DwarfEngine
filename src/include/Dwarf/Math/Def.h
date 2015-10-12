#ifndef MATH_DEF_H
#define MATH_DEF_H

#include "../DwarfSetup.h"

namespace Dwarf
{
	namespace Math
	{
		#define PI 3.14159265359

		// Macros for declaring and defining global / and * operators with given type and class
		#define DECLARE_DIV_MUL_OPERATORS(type, primitive) \
		DWARFAPI type operator / (const primitive &lhs, const type &rhs); \
		DWARFAPI type operator * (const primitive &lhs, const type &rhs);

		#define DEFINE_DIV_MUL_OPERATORS(type, primitive) \
		DWARFAPI type operator / (const primitive &lhs, const type &rhs) \
		{ return rhs / lhs; } \
		DWARFAPI type operator * (const primitive &lhs, const type &rhs) \
		{ return rhs * lhs; }

	}
}

#endif
