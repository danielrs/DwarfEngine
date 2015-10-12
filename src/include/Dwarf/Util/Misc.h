#ifndef UTIL_MISC_H
#define UTIL_MISC_H

namespace Dwarf
{
	namespace Util
	{
		#define SAFE_DELETE(ptr) if (ptr) { delete ptr; ptr = 0; }
		#define UNUSED(x) (void)(x)	
	}
}
#endif