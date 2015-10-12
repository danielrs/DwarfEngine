#ifndef DWARF_UTIL_DISPOSABLE_H
#define DWARF_UTIL_DISPOSABLE_H

#include "../DwarfSetup.h"

/**
 * This interface provides a mechanism for releasing unmanaged resource
 */

namespace Dwarf {
	namespace Util {

		class DWARFAPI IDisposable {
		public:
			virtual ~IDisposable();
			virtual void dispose() = 0;
		};

	}
}

#endif
