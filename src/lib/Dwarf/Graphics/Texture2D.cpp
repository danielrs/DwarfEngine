#include <Dwarf/Graphics/Texture2D.h>
#include <Dwarf/Graphics/Image.h>
#include <Dwarf/Util/Exceptions.h>

using namespace Dwarf::Util;
using namespace std;

namespace Dwarf {
	namespace Graphics {

		Texture2DResource::Texture2DResource() : Texture(GL_TEXTURE_2D) {
		}

		string Texture2DResource::getFilename() const {
			return filename;
		}

		bool Texture2DResource::isLoaded() const {
			return loaded;
		}

		void Texture2DResource::unload() {
			Texture::dispose();
			loaded = false;
		}

		void Texture2DResource::load(const string &filename) {
			int img_w, img_h;
			unsigned char* img = Image::load(filename.c_str(), &img_w, &img_h, DWARF_RGBA);

			if (img) {
				this->filename = filename;
				this->width = img_w;
				this->height = img_h;

				glGenTextures(1, &texture_id);
				glBindTexture(texture_target, texture_id);
				glTexStorage2D(texture_target, 1, GL_RGBA8, img_w, img_h);
				glTexSubImage2D(texture_target, 0, 0, 0, img_w, img_h, GL_RGBA, GL_UNSIGNED_BYTE, img);

				glGenerateMipmap(texture_target);
				setMinFilter(min_filter);
				setMagFilter(mag_filter);
				glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

				this-> loaded = true;
			} else {
				throw FileNotFoundException(filename);
				this->loaded = false;
			}
		}

		size_t Texture2DResource::getWidth() const {
			return this->width;
		}

		size_t Texture2DResource::getHeight() const {
			return this->height;
		}

	} // namespace Graphics
} // namespace Dwarf
