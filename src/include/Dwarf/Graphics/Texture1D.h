#ifndef DWARF_GRAPHICS_TEXTURE1D_H
#define DWARF_GRAPHICS_TEXTURE1D_H

#include "../DwarfSetup.h"
#include "Texture.h"
#include "../Util/IResource.h"

#include <memory>

namespace Dwarf
{
	namespace Graphics
	{

		class DWARFAPI Texture1DResource : public Texture, public Util::IResource
		{
		public:
			Texture1DResource();

			std::string getFilename() const override;
			bool isLoaded() const override;
			void unload() override;
			void load(const std::string &filename) override;

			size_t getWidth() const;

		private:
			std::string filename;
			bool loaded;
			size_t width;
		};

		using Texture1D = std::shared_ptr<Texture1DResource>;
	}
}

#endif
