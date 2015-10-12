#ifndef DWARF_GRAPHICS_IMAGE_H
#define DWARF_GRAPHICS_IMAGE_H

#include "../DwarfSetup.h"
#include <string>

namespace Dwarf {
	namespace Graphics {

		enum DWARFAPI ImageFormat {
			DWARF_RGB = 3,
			DWARF_RGBA = 4
		};

		class DWARFAPI Image {
		public:
			static unsigned char* load(const std::string &filename, int *w, int *h, const ImageFormat &format);
		};
	}
}

#endif