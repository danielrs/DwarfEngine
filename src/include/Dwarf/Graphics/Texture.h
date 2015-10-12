#ifndef DWARF_GRAPHICS_TEXTURE_H
#define DWARF_GRAPHICS_TEXTURE_H

#include "../DwarfSetup.h"
#include GLEW_H
#include "../Util/IDisposable.h"

#include <string>

namespace Dwarf
{
	namespace Graphics
	{
		enum class DWARFAPI TextureFilter : int {
			NEAREST = 0,
			LINEAR,
			NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR
		};

		class DWARFAPI Texture : public Util::IDisposable {
		public:
			Texture(GLenum texture_target);
			virtual ~Texture();
			void dispose() override;

			TextureFilter getMinFilter() const;
			void setMinFilter(const TextureFilter &filter);
			TextureFilter getMagFilter() const;
			void setMagFilter(const TextureFilter &filter);

			void unbind() const;
			void bind(GLenum texture_unit) const;
			GLuint getID() const;
		protected:
			void setTarget(GLenum target);

			GLuint texture_id;
			GLuint texture_target;
			TextureFilter min_filter;
			TextureFilter mag_filter;
		private:
			static GLenum filters[];
		};

	} // namespace Graphics
} // namespace Dwarf
#endif
