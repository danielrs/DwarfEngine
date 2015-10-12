#ifndef LOGGER_H
#define LOGGER_H

#include "../DwarfSetup.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <cstdarg>
#include <string>

namespace Dwarf
{
	namespace Util
	{

		class DWARFAPI Logger
		{
		private:
			// Prints to Debug
			static int print(const std::string &format, va_list argList);
		public:
			enum VERBOSITY_LEVEL
			{
				V_NONE		= 0x0,
				V_NORMAL	= 0x1,
				V_WARNING	= 0x2,
				V_ERROR		= 0x3
			};

			static VERBOSITY_LEVEL v_level;

			// Methods
			// Checks verbosity level and calls private print
			static int log(const VERBOSITY_LEVEL &level, std::string format, ...);
		};

	}
}

#endif
