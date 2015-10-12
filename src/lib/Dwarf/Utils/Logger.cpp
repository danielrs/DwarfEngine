#include <Dwarf/Util/Logger.h>
#include <cstdio>

#include <iostream>
using namespace std;

namespace Dwarf
{
	namespace Util
	{

		Logger::VERBOSITY_LEVEL Logger::v_level = Logger::V_ERROR;

		// ----------------------------------------------------------------

		int Logger::print(const string &format, va_list argList)
		{
			const size_t MAX_CHARS = 2048;
			char buffer[MAX_CHARS + 1];

			int charsWritten = vsnprintf(buffer, MAX_CHARS, format.c_str(), argList);
			buffer[MAX_CHARS] = '\0';

			// Call OutputDebugString (WIN32 API)
			#ifdef _MSC_VER
				OutputDebugString(buffer);
			#else
				cerr << buffer;
			#endif


			return charsWritten;
		}

		// ----------------------------------------------------------------

		int Logger::log(const VERBOSITY_LEVEL &level, string format, ...)
		{
			if (level <= Logger::v_level)
			{
				va_list argList;
				va_start(argList, format);

				int charsWritten = Logger::print(format, argList);

				va_end(argList);

				return charsWritten;
			}

			return 0;
		}

	} // End of namespace Util
} // End of namespace Dwarf
