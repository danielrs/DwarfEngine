#include <Dwarf/Graphics/Texture.h>
#include <Dwarf/Util/Exceptions.h>

using namespace Dwarf::Util;

namespace Dwarf
{
	namespace Graphics
	{

		GLenum Texture::filters[] = {
			GL_NEAREST,
			GL_LINEAR,
			GL_NEAREST_MIPMAP_NEAREST,
			GL_LINEAR_MIPMAP_NEAREST,
			GL_NEAREST_MIPMAP_LINEAR,
			GL_LINEAR_MIPMAP_LINEAR
		};

		Texture::Texture(GLenum texture_target)
		:
			texture_id(0), texture_target(texture_target),
			min_filter(TextureFilter::LINEAR_MIPMAP_LINEAR), mag_filter(TextureFilter::LINEAR)
		{}

		Texture::~Texture()
		{
			dispose();
		}

		void Texture::dispose() {
			if (glIsTexture(texture_id)) {
				glDeleteTextures(1, &texture_id);
			}
		}

		TextureFilter Texture::getMinFilter() const {
			return min_filter;
		}

		void Texture::setMinFilter(const TextureFilter &filter) {
			glBindTexture(texture_target, texture_id);
			glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, filters[static_cast<int>(filter)]);
			this->min_filter = filter;
		}

		TextureFilter Texture::getMagFilter() const {
			return mag_filter;
		}

		void Texture::setMagFilter(const TextureFilter &filter) {
			if (filter != TextureFilter::NEAREST && filter != TextureFilter::LINEAR)
				throw IllegalArgumentException("Magnification filter must be either NEAREST or LINEAR");

			glBindTexture(texture_target, texture_id);
			glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, filters[static_cast<int>(filter)]);
			this->mag_filter = filter;
		}


		void Texture::unbind() const {
			glBindTexture(texture_target, 0);
		}

		void Texture::bind(GLenum texture_unit) const
		{
			glActiveTexture(texture_unit);
			glBindTexture(texture_target, texture_id);
		}

		GLuint Texture::getID() const
		{
			return this->texture_id;
		}

		void Texture::setTarget(GLenum target)
		{
			this->texture_target = target;
		}

	} // end of namespace Graphics
} // end of namespace Dwarf
