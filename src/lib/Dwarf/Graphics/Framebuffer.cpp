#include <Dwarf/Graphics/Framebuffer.h>

namespace Dwarf {
	namespace Graphics {

		Framebuffer::Framebuffer(const GLenum &pixel_format, const unsigned int &width, const unsigned int &height, const bool &has_depth) {
			this->pixel_format = pixel_format;
			this->width = width;
			this->height = height;
			this->has_depth = has_depth;
			this->has_stencil = false;
		}

		Framebuffer::Framebuffer(const GLenum &pixel_format, const unsigned int &width, const unsigned int &height, const bool &has_depth, const bool &has_stencil) {
			this->pixel_format = pixel_format;
			this->width = width;
			this->height = height;
			this->has_depth = has_depth;
			this->has_stencil = has_stencil;
		}

		Framebuffer::~Framebuffer() {
		}

		void Framebuffer::dispose() {
			if (glIsFramebuffer(FBO)) {
				glDeleteFramebuffers(1, &FBO);
			}
			color_buffer.dispose();
			depth_buffer.dispose();
			/* stencil_buffer.dispose(); */
		}

		void Framebuffer::bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		}

		void Framebuffer::unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Framebuffer::gen() {
			this->dispose();

			glGenFramebuffers(1, &FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			color_buffer.setPixelFormat(pixel_format);
			color_buffer.setWidth(width);
			color_buffer.setHeight(height);
			color_buffer.gen();
			if (has_depth) {
				depth_buffer.setPixelFormat(GL_DEPTH_COMPONENT32F);
				depth_buffer.setWidth(width);
				depth_buffer.setHeight(height);
				depth_buffer.gen();
			}
			if (has_stencil) {
				// TODO: Add Stencil
			}
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color_buffer.getID(), 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_buffer.getID(), 0);
			static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, draw_buffers);
		}

		GLuint Framebuffer::getID() const {
			return FBO;
		}

		GLenum Framebuffer::getPixelFormat() const {
			return pixel_format;
		}

		void Framebuffer::setPixelFormat(const GLenum &pixel_format) {
			this->pixel_format = pixel_format;
		}

		int Framebuffer::getWidth() const {
			return width;
		}

		void Framebuffer::setWidth(const int &width) {
			this->width = width;
		}

		int Framebuffer::getHeight() const {
			return height;
		}

		void Framebuffer::setHeight(const int &height) {
			this->height = height;
		}

		const Texture2DBuffer* Framebuffer::getColorBuffer() const {
			return &color_buffer;
		}

		const Texture2DBuffer* Framebuffer::getDepthBuffer() const {
			return &depth_buffer;
		}

		const Texture2DBuffer* Framebuffer::getStencilBuffer() const {
			/* return stencil_buffer; */
			return &depth_buffer;
		}

	} // namespace Graphics
} // namespace Dwarf
