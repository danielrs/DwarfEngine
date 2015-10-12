#include <Dwarf/Graphics/Texture1D.h>
#include <Dwarf/Graphics/Image.h>
#include <Dwarf/Util/Exceptions.h>

using namespace Dwarf::Util;
using namespace std;

namespace Dwarf {
	namespace Graphics {

		Texture1DResource::Texture1DResource() : Texture(GL_TEXTURE_1D) {
		}

		string Texture1DResource::getFilename() const {
			return filename;
		}

		bool Texture1DResource::isLoaded() const {
			return loaded;
		}

		void Texture1DResource::unload() {
			Texture::dispose();
			loaded = false;
		}

		void Texture1DResource::load(const string &filename) {
			int img_w, img_h;
			unsigned char* img = Image::load(filename.c_str(), &img_w, &img_h, DWARF_RGBA);

			if (img) {
				this->filename = filename;
				this->width = img_w * img_h;

				glGenTextures(1, &texture_id);
				glBindTexture(texture_target, texture_id);
				glTexImage1D(texture_target, 0, GL_RGBA8, this->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

				glGenerateMipmap(texture_target);
				setMinFilter(min_filter);
				setMagFilter(mag_filter);
				glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

				this->loaded = true;
			} else {
				throw FileNotFoundException(filename);
				this->loaded = false;
			}
		}

		size_t Texture1DResource::getWidth() const {
			return this->width;
		}

	} // namespace Graphics
} // namespace Dwarf
