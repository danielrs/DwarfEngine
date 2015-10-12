#ifndef DWARF_GRAPHICS_TEXTURE2DBUFFER_H
#define DWARF_GRAPHICS_TEXTURE2DBUFFER_H

/**
 * Empty OpenGL textures wrapper for any use (E.g. Color Buffer, Depth Buffer, Stencil Bufferk, ...)
 */

#include "../DwarfSetup.h"
#include "Texture.h"

namespace Dwarf
{
	namespace Graphics
	{

		class DWARFAPI Texture2DBuffer : public Texture
		{
		public:
			Texture2DBuffer();
			Texture2DBuffer(const GLenum &pixel_format);
			Texture2DBuffer(const GLenum &pixel_format, const int &width, const int &height);

			/**
			 * Generates the texture
			 */
			void gen();

			GLenum getPixelFormat() const;
			void setPixelFormat(const GLenum &pixel_format);
			int getWidth() const;
			void setWidth(const int &width);
			int getHeight() const;
			void setHeight(const int &height);

		private:
			GLuint pixel_format;
			int width;
			int height;

		};

	}
}

#endif
