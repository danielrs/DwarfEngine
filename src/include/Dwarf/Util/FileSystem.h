#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "../DwarfSetup.h"

#include <string>

namespace Dwarf {
	namespace Util {

		class DWARFAPI FileSystem {

		public:
			static std::string loadFile(const std::string &path);
		};
	}
}

#endif