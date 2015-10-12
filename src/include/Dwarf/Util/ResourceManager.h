#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../DwarfSetup.h"
#include "IResource.h"
#include "Singleton.h"
#include "Exceptions.h"

// Resources
#include "../Graphics/Texture1D.h"
#include "../Graphics/Texture2D.h"
/* #include "../Graphics/Mesh.h" */

#include <iostream>
#include <map>
#include <memory>

namespace Dwarf {
	namespace Util {

		class DWARFAPI ResourceManager : public Singleton<ResourceManager> {
		public:
			template <typename T>
			T load(const std::string &filename); // Typechecking only
		protected:
			template <typename T>
			std::shared_ptr<T> load_(const std::string &filename); // Does the actual loading
		private:
			std::map<std::string, std::weak_ptr<IResource>> resource_cache_;
		};


	} // namespace Util
} // namespace Dwarf

// ------------------
// Template definitions
// ------------------

namespace Dwarf {
	namespace Util {

		template <typename T>
		DWARFAPI T ResourceManager::load(const std::string &filename) {
			throw ResourceTypeNotValidException();
		}

		// Specializations
		template <>
		DWARFAPI Graphics::Texture1D ResourceManager::load<Graphics::Texture1D>(const std::string &filename);

		template <>
		DWARFAPI Graphics::Texture2D ResourceManager::load<Graphics::Texture2D>(const std::string &filename);

		/* template <> */
		/* DWARFAPI Graphics::Mesh ResourceManager::load<Graphics::Mesh>(const std::string &filename); */

		// ------------------

		// Actual loading
		template <typename T>
		std::shared_ptr<T> ResourceManager::load_(const std::string &filename) {

			using namespace std;
			using namespace Graphics;

			static_assert(std::is_base_of<IResource, T>::value, "Typename must derive Resource class!");

			try {
				auto it = resource_cache_.find(filename);

				if (it != resource_cache_.end() && !resource_cache_[filename].expired()) {
					return dynamic_pointer_cast<T>(resource_cache_[filename].lock());
				}

				T *tex_res = new T();
				tex_res->load(filename);
				shared_ptr<T> new_tex_res(tex_res);
				resource_cache_[filename] = new_tex_res;

				return dynamic_pointer_cast<T>(resource_cache_[filename].lock());

			} catch (FileNotFoundException e) {
				cerr << "Failed to load resource: " << filename << endl;
				cerr << "Exception: " << e.what() << endl;
			}

			return nullptr;
		} // load_

	} // namespace Util
} // namespace Dwarf

#endif
