#ifndef DWARF_GRAPHICS_SPRITE_H
#define DWARF_GRAPHICS_SPRITE_H

#include "../DwarfSetup.h"
#include "Texture2D.h"
#include "../Math/Rectangle.h"
#include "../Math/Vector2.h"

namespace Dwarf {

	namespace Graphics {

		class DWARFAPI Sprite {
		public:
			Math::Vector2 position;
			Math::Vector2 scale;
			float rotation;

			Sprite();
			Sprite(Texture2D texture);

			Texture2D getTexture() const;
			/**
			 * Changes the Sprite's texture and changes the
			 * region to whole surface
			 */
			void setTexture(Texture2D texture);
			/**
			 * Changes the Sprite's texture without changing
			 * the region (unless it has not been set)
			 */
			void updateTexture(Texture2D texture);

			Math::Rectangle getRegion() const;
			void setRegion(const int &x, const int &y, const int &w, const int &h);
			void setRegion(const Math::Rectangle &rect);
		private:
			Texture2D texture_;
			Math::Rectangle region_; ///< Region to be used when drawing the texture (e.g. Atlases)
		};

	}
}
#endif
