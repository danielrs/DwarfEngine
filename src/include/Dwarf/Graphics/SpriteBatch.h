#ifndef DWARF_GRAPHICS_SPRITEBATCH_H
#define DWARF_GRAPHICS_SPRITEBATCH_H

#include "../DwarfSetup.h"
#include GLEW_H
#include "Camera2D.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture2D.h"

#include <vector>

namespace Dwarf {
	namespace Graphics {

		class DWARFAPI SpriteBatch {
		public:
			/**
			 * Initializes a SpriteBatch of default size (8192 sprites)
			 */
			SpriteBatch();

			/**
			 * Initializes a SpriteBatch of @size sprites
			 * the total size of the OpenGL buffer created
			 * is @size * 64 bytes
			 * @param size the maximum size of the batch
			 */
			SpriteBatch(const size_t &size);
			~SpriteBatch();
			void begin();
			void begin(const Camera2D& camera);

			/**
			 * Adds the given sprite to the batch, if the batch limit is exceeded
			 * all sprites in batch are drawn and cleared from the buffer
			 * @param Sprite the sprite to be drawn
			 */
			void draw(const Sprite& sprite);

			/**
			 * Draws everything in the batch buffer
			 */
			void end();

			/**
			 * Returns the number of OpenGL draw calls since
			 * last SpriteBatch.begin was called
			 * @returns int the number of OpenGL draw calls
			 */
			int renderCalls();

		private:
			bool drawing_;

			// OpenGL stuff
			GLuint VAO_;
			GLuint VBO_;
			GLuint IBO_;

			ShaderProgram program_;

			// Camera
			const Camera2D *camera_;

			// Sprite Index
			int MAX_SPRITES_; // 64 bytes of vertex data per sprite (vertices and uvs) = 512KB of VRAM for vertex data
			int sprite_index_;
			int render_calls_;
			// Texture buffer
			std::vector<Texture2D> textures_; // Don't forget that Texture type is a shared pointer

			// Private methods
			void clear_();
			void flush_(); // Draws everything and clears the buffers
		};
	}
}
#endif
