#include <Dwarf/Util/Singleton.h>
#include <Dwarf/Util/ResourceManager.h>
#include <Dwarf/Util/Time.h>

namespace Dwarf
{
	namespace Util
	{

		// Force the compiler to instantiate these singletons
		template class Singleton<Time>;
		template class Singleton<ResourceManager>;
	}
}
