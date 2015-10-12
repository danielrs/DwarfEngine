#include <Dwarf/Util/ResourceManager.h>

#include <string>

using namespace Dwarf::Graphics;
using namespace std;

namespace Dwarf {
	namespace Util {

		/**
		 * Instantiates the singleton at compile time (required for DLL)
		 */
		 #ifndef DWARF_STATIC
		void instantiate_resource_manager()
		{
			Singleton<ResourceManager>::INSTANCE();
		}
		#endif // DWARF_STATIC

		// --------------------------------

		template <>
		Graphics::Texture1D ResourceManager::load<Graphics::Texture1D>(const string &filename) {
			return this->load_<Texture1DResource>(filename);
		}

		template <>
		Graphics::Texture2D ResourceManager::load<Graphics::Texture2D>(const string &filename) {
			return this->load_<Texture2DResource>(filename);
		}

		/* template <> */
		/* Graphics::Mesh ResourceManager::load<Graphics::Mesh>(const string &filename) { */
		/* 	return this->load_<MeshResource>(filename); */
		/* } */

	} // namespace Util
} // namespace Dwarf
