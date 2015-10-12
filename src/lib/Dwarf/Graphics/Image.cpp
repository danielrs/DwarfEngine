#include <Dwarf/Graphics/Image.h>

#define STB_IMAGE_IMPLEMENTATION
#include STB_IMAGE_H

using namespace std;

namespace Dwarf {
	namespace Graphics {

		unsigned char* Image::load(const string &filename, int *w, int *h, const ImageFormat &format)
		{
			FILE *file = fopen(filename.c_str(), "rb");

			if (file) {

				// horizontal pixels, vertical pixels, and components
				int x, y, comp;
				unsigned char* data;

				data = stbi_load_from_file(file, &x, &y, &comp, 0);
				fclose(file);

				*w = x;
				*h = y;

				// NOTE: OpenGL's texture origin is bottom-right
				// stb_image origin is top-left, we need to fix that.
				// See: http://stackoverflow.com/questions/19770296/should-i-vertically-flip-the-lines-of-an-image-loaded-with-stb-image-to-use-in-o
				unsigned char* user_data = new unsigned char[x * y * format];
				for (int j = 0; j < y; ++j) {
					for (int i = 0; i < x; ++i) {
						// Start filling user_data from the last row up to the first one
						user_data[(x * (y - j - 1) + i) * format + 0] = data[(x*j + i)*comp + 0];
						user_data[(x * (y - j - 1) + i) * format + 1] = data[(x*j + i)*comp + 1];
						user_data[(x * (y - j - 1) + i) * format + 2] = data[(x*j + i)*comp + 2];
						user_data[(x * (y - j - 1) + i) * format + 3] = 0xFF;
						// User asked for RGBA?
						if (format == DWARF_RGBA && comp == 4)
							user_data[(x * (y - j - 1) + i) * format + 3] = data[(x*j + i)*comp + 3];
					}
				}
				stbi_image_free(data);

				return user_data;
			}

			return nullptr;
		}

	}
}
