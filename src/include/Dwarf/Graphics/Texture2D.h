#ifndef DWARF_GRAPHICS_TEXTURE2D_H
#define DWARF_GRAPHICS_TEXTURE2D_H

#include "../DwarfSetup.h"
#include "Texture.h"
#include "../Util/IResource.h"

#include <memory>

namespace Dwarf
{
	namespace Graphics
	{

		class DWARFAPI Texture2DResource : public Texture, public Util::IResource
		{
		public:
			Texture2DResource();

			std::string getFilename() const override;
			bool isLoaded() const override;
			void unload() override;
			void load(const std::string &filename) override;

			size_t getWidth() const;
			size_t getHeight() const;

		private:
			std::string filename;
			bool loaded;
			size_t width;
			size_t height;
		};

		using Texture2D = std::shared_ptr<Texture2DResource>;

	}
}

#endif
