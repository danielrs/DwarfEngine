#include <Dwarf/Graphics/SpriteBatch.h>
#include <Dwarf/Graphics/Sprite.h>
#include <Dwarf/Graphics/Shader.h>
#include <Dwarf/Graphics/Shaders/Shaders.h>
#include <Dwarf/Util/Exceptions.h>
#include <iostream>

#include OPENGL_H
#include GLEW_H

using namespace std;
using namespace Dwarf::Math;
using namespace Dwarf::Util;

namespace Dwarf {
	namespace Graphics {

		// Vertex struct used for better handling of data
		struct Vertex {
			float x, y;
			float uvx, uvy;
		};

		// ------------------

		SpriteBatch::SpriteBatch() {
			this->drawing_ = false;
			this->MAX_SPRITES_ = 8192;
			this->textures_.reserve(MAX_SPRITES_);
		}

		SpriteBatch::SpriteBatch(const size_t &size) {
			this->drawing_ = false;
			this->MAX_SPRITES_ = size;
			this->textures_.reserve(MAX_SPRITES_);
		}

		SpriteBatch::~SpriteBatch() {
			// Delete them when destroying batch
			// but create them lazily (at begin)
			glDeleteVertexArrays(1, &VAO_);
			glDeleteBuffers(1, &VBO_);
			glDeleteBuffers(1, &IBO_);
		}

		void SpriteBatch::begin() {
			Camera2D camera(800, 600);
			this->begin(camera);
		}

		void SpriteBatch::begin(const Camera2D& camera) {

			if (this->drawing_) throw IllegalStateException("SpriteBatch.end must be called before begin.");
			this->drawing_ = true;

			// Only generate them the first time begin is called
			if (!glIsVertexArray(VAO_)) {
				glGenVertexArrays(1, &VAO_);
				glGenBuffers(1, &VBO_);
				glGenBuffers(1, &IBO_);

				glBindVertexArray(VAO_);
				glBindBuffer(GL_ARRAY_BUFFER, VBO_);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);

				// Buffers will be loaded dynamically using glMapBufferRange
				glBufferData(GL_ARRAY_BUFFER, MAX_SPRITES_ * sizeof(Vertex) * 4, NULL, GL_DYNAMIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_SPRITES_ * 6 * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);

				// Layout of vertex attributes
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvx));
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

			}

			// Compile program
			if (!program_.isLinked()) {
				Shader vert_shader = Shader(Shader::VERTEX, Shaders::spritebatch_vert);
				Shader frag_shader = Shader(Shader::FRAGMENT, Shaders::spritebatch_frag);
				program_.attachShader(&vert_shader);
				program_.attachShader(&frag_shader);
				program_.link();
			}

			// Other
			this->camera_ = &camera;
			this->clear_();
			this->render_calls_ = 0;
		}

		// ------------------

		void SpriteBatch::draw(const Sprite& sprite) {

			// Exception and flushing
			if (!drawing_) throw IllegalStateException("SpriteBatch.begin must be called before draw!");
			if (sprite_index_ >= MAX_SPRITES_) this->flush_();

			// Map buffers
			glBindBuffer(GL_ARRAY_BUFFER, VBO_);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);

			Vertex* vbuff = (Vertex*) glMapBufferRange(
				GL_ARRAY_BUFFER, sprite_index_ * sizeof(Vertex) * 4,
				sizeof(Vertex) * 4,
				GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
			);

			unsigned int* ibuff = (unsigned int*) glMapBufferRange(
				GL_ELEMENT_ARRAY_BUFFER,
				sprite_index_ * sizeof(unsigned int) * 6,
				sizeof(unsigned int) * 6,
				GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
			);

			int half_width = sprite.getRegion().size.x/2;
			int half_height = sprite.getRegion().size.y/2;
			vbuff[0].x = -half_width; vbuff[0].y = -half_height;
			vbuff[1].x = half_width; vbuff[1].y = -half_height;
			vbuff[2].x = half_width; vbuff[2].y = half_height;
			vbuff[3].x = -half_width; vbuff[3].y = half_height;

			float rads = sprite.rotation / 180 * PI;
			for (int i = 0;i < 4; ++i) {
				// Scale
				vbuff[i].x *= sprite.scale.x;
				vbuff[i].y *= sprite.scale.y;
				// Rotate
				float x = vbuff[i].x;
				float y = vbuff[i].y;
				vbuff[i].x = x*cos(rads) - y*sin(rads);
				vbuff[i].y = x*sin(rads) + y*cos(rads);
				// Translate
				vbuff[i].x += sprite.position.x;
				vbuff[i].y += sprite.position.y;
			}

			// TODO: UV coordinates should be set
			// using the sprite's clip_rect member
			vbuff[0].uvx = 0; vbuff[0].uvy = 0;
			vbuff[1].uvx = 1; vbuff[1].uvy = 0;
			vbuff[2].uvx = 1; vbuff[2].uvy = 1;
			vbuff[3].uvx = 0; vbuff[3].uvy = 1;

			ibuff[0] = sprite_index_*4 + 0;
			ibuff[1] = sprite_index_*4 + 1;
			ibuff[2] = sprite_index_*4 + 3;
			ibuff[3] = sprite_index_*4 + 3;
			ibuff[4] = sprite_index_*4 + 1;
			ibuff[5] = sprite_index_*4 + 2;

			// Textures
			textures_.push_back(sprite.getTexture());

			// Unmap
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

			this->sprite_index_++;
		}

		// ------------------

		void SpriteBatch::end() {
			if (!this->drawing_) throw IllegalStateException("SpriteBatch.begin must be called before end.");
			this->drawing_ = false;
			this->flush_();
		}

		// ------------------

		int SpriteBatch::renderCalls() {
			return this->render_calls_;
		}

		// ------------------

		void SpriteBatch::clear_() {
			this->sprite_index_ = 0;
			this->textures_.clear();
		}

		// ------------------

		void SpriteBatch::flush_() {

			if (sprite_index_ <= 0) return;

			glUseProgram(program_.getID());
			glBindVertexArray(VAO_);

			program_.setUniformMatrix(
				program_.getUniformLocation("MVP_MATRIX"),
				this->camera_->getCameraMatrix(),
				true
			);

			Texture2D old_texture = textures_[0];
			int offset = 0;
			for (int i = 1; i < sprite_index_; ++i) {

				if (textures_[i] != old_texture) {
					// Draw until now
					old_texture->bind(GL_TEXTURE0);
					glDrawElements(GL_TRIANGLES, (i - offset) * 6, GL_UNSIGNED_INT, (void*)(offset * 6 * sizeof(unsigned int)));
					this->render_calls_++;

					offset = i;
					old_texture = textures_[i];
				}
			}
			// Draw what's left
			old_texture->bind(GL_TEXTURE0);
			glDrawElements(GL_TRIANGLES, (sprite_index_ - offset) * 6, GL_UNSIGNED_INT, (void*)(offset * 6 * sizeof(unsigned int)));
			this->render_calls_++;

			// Un-bind data
			/* glBindVertexArray(0); */
			glUseProgram(0);

			this->clear_();
		}

	}
}
