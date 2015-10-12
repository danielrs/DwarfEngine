#include <Dwarf/Graphics/Shaders/Shaders.h>

namespace Dwarf {
	namespace Graphics {
		namespace Shaders {

			#define HASH(A) A
			#define XSTRINGIFY(A) STRINGIFY(A)
			#define STRINGIFY(A) #A
			#define GLSL(A) "#version 430 core\n" STRINGIFY(A)

			#include "FullQuad.vert"
			#include "FullQuad.frag"
			#include "PositionColor.vert"
			#include "PositionColor.frag"
			#include "PositionTexture.vert"
			#include "PositionTexture.frag"
			#include "SpriteBatch.vert"
			#include "SpriteBatch.frag"

			#include "BloomFX.frag"
			#include "BloomCombineFX.frag"
			#include "GaussBlurFX.frag"
		}
	}
}
