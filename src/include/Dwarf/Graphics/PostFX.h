#ifndef DWARF_GRAPHICS_POSTX_H
#define DWARF_GRAPHICS_POSTX_H

#include "../DwarfSetup.h"

namespace Dwarf {
	namespace Graphics {

		// Forward declare
		class Framebuffer;

		class DWARFAPI PostFX {
		public:
			virtual ~PostFX();
			virtual void apply(Framebuffer *framebuffer) = 0;
		};

	}
}
#endif
