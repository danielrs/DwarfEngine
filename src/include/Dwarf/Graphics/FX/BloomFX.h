#ifndef DWARF_GRAPHICS_BLOOMFX_H
#define DWARF_GRAPHICS_BLOOMFX_H

#include "../../DwarfSetup.h"
#include "../PostFX.h"
#include "../ShaderProgram.h"
#include "../Texture2DBuffer.h"
#include "../../Util/IDisposable.h"

namespace Dwarf {
	namespace Graphics {

		class DWARFAPI BloomFX : public PostFX, public Util::IDisposable {
		public:
			BloomFX();
			void dispose() override;
			float getBloomFactor() const;
			void setBloomFactor(const float &bloom_factor);
			void apply(Framebuffer *framebuffer) override;
		private:
			float bloom_factor;

			ShaderProgram light_program;
			ShaderProgram blur_program;
			ShaderProgram comb_program;
			// Buffers for gaussian blur
			Texture2DBuffer buffer1;
			Texture2DBuffer buffer2;
			void gen(Framebuffer *framebuffer);
		};

	}
}
#endif
