#ifndef DWARF_UTIL_IRESOURCE_H
#define DWARF_UTIL_IRESOURCE_H

/**
 * Interface that describes an unmanaged resource
 */

#include "../DwarfSetup.h"

#include <string>

namespace Dwarf {
	namespace Util {

		class DWARFAPI IResource {
		public:
			virtual ~IResource();
			virtual std::string getFilename() const = 0;
			virtual bool isLoaded() const = 0;
			virtual void unload() = 0;
			virtual void load(const std::string &filename) = 0;
		};

	}
}
#endif
