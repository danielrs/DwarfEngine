#include <Dwarf/Graphics/Texture2DBuffer.h>

#include <iostream>
using namespace std;

namespace Dwarf {
	namespace Graphics {

		Texture2DBuffer::Texture2DBuffer() : Texture(GL_TEXTURE_2D) {
			this->pixel_format = GL_RGBA8;
		}

		Texture2DBuffer::Texture2DBuffer(const GLenum &pixel_format) : Texture(GL_TEXTURE_2D) {
			this->pixel_format = pixel_format;
		}

		Texture2DBuffer::Texture2DBuffer(const GLenum &pixel_format, const int &width, const int &height) : Texture(GL_TEXTURE_2D) {
			this->pixel_format = pixel_format;
			this->width = width;
			this->height = height;
		}

		void Texture2DBuffer::gen() {
			this->dispose();

			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);
			glTexStorage2D(GL_TEXTURE_2D, 9, pixel_format, width, height);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLenum Texture2DBuffer::getPixelFormat() const {
			return pixel_format;
		}

		void Texture2DBuffer::setPixelFormat(const GLenum &pixel_format) {
			this->pixel_format = pixel_format;
		}

		int Texture2DBuffer::getWidth() const {
			return width;
		}

		void Texture2DBuffer::setWidth(const int &width) {
			this->width = width;
		}

		int Texture2DBuffer::getHeight() const {
			return height;
		}

		void Texture2DBuffer::setHeight(const int &height) {
			this->height = height;
		}

	}
}
