#ifndef DWARF_GRAPHICS_FRAMEBUFFER_H
#define DWARF_GRAPHICS_FRAMEBUFFER_H

#include "../DwarfSetup.h"
#include GLEW_H
#include "Texture2DBuffer.h"
#include "../Util/IDisposable.h"

namespace Dwarf {
	namespace Graphics {

		class DWARFAPI Framebuffer : public Util::IDisposable {
		public:
			Framebuffer(const GLenum &pixel_format, const unsigned int &width, const unsigned int &height, const bool &has_depth);
			Framebuffer(const GLenum &pixel_format, const unsigned int &width, const unsigned int &height, const bool &has_depth, const bool &has_stencil);
			~Framebuffer();
			void dispose() override;

			void bind();
			void unbind();
			void gen();

			GLuint getID() const;
			GLenum getPixelFormat() const;
			void setPixelFormat(const GLenum &pixel_format);
			int getWidth() const;
			void setWidth(const int &width);
			int getHeight() const;
			void setHeight(const int &height);

			const Texture2DBuffer* getColorBuffer() const;
			const Texture2DBuffer* getDepthBuffer() const;
			const Texture2DBuffer* getStencilBuffer() const;

		private:
			GLuint FBO;
			GLuint pixel_format;
			int width;
			int height;
			bool has_depth;
			bool has_stencil;
			Texture2DBuffer color_buffer;
			Texture2DBuffer depth_buffer;
			/* Texture2DBuffer stencil_buffer; */
		};

	}
}

#endif
