#ifndef SHADERS_H
#define SHADERS_H

#include "../../DwarfSetup.h"

namespace Dwarf {
	namespace Graphics {
		namespace Shaders {

			extern DWARFAPI const char* fullquad_vert;
			extern DWARFAPI const char* fullquad_frag;
			extern DWARFAPI const char* position_color_vert;
			extern DWARFAPI const char* position_color_frag;
			extern DWARFAPI const char* position_texture_vert;
			extern DWARFAPI const char* position_texture_frag;
			extern DWARFAPI const char* spritebatch_vert;
			extern DWARFAPI const char* spritebatch_frag;

			extern DWARFAPI const char* gaussblurfx_frag;
			extern DWARFAPI const char* bloomfx_frag;
			extern DWARFAPI const char* bloomcombinefx_frag;
		}
	}
}

#endif
