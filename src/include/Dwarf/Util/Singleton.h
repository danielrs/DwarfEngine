#ifndef SINGLETON_H
#define SINGLETON_H

#include "../DwarfSetup.h"

namespace Dwarf
{
	namespace Util
	{

		template <typename T>
		class DWARFAPI Singleton
		{
		private:
			Singleton(Singleton const&) = delete;
			void operator=(Singleton const&) = delete;
		protected:
			Singleton() {};
			~Singleton() {};

		public:
			static T& INSTANCE();
		};

		template<typename T>
		T& Singleton<T>::INSTANCE()
		{
			static T instance;
			return instance;
		}

	}
}

#endif
