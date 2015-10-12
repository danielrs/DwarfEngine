#ifndef TIME_H
#define TIME_H

#include "../DwarfSetup.h"
#include "Singleton.h"

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__) || defined(__linux)
#include <chrono>
#endif

namespace Dwarf
{
	namespace Util
	{

		class DWARFAPI Time : public Singleton<Time>
		{
		private:
			float delta_time;
			float alpha_time;

			#ifdef _WIN32
			LARGE_INTEGER CLOCK_FREQUENCY;
			LARGE_INTEGER START_STEP;
			LARGE_INTEGER last_step;
			#elif defined(__APPLE__) || defined(__linux)
			std::chrono::time_point<std::chrono::high_resolution_clock> START_STEP;
			std::chrono::time_point<std::chrono::high_resolution_clock> last_step;
			#endif
		public:
			// The Fixed step used in the GameLoop
			float fixed_step;

			// Initializes the class
			void initialize();

			// Updates the delta_time
			void step();

			// Returns the time the program has been running, in seconds
			float current() const;

			// Returns the time elapsed since the last frame, in seconds
			float delta() const;

			// Returns the alpha time of each frame
			float alpha() const;
			// Sets the alpha_time
			void setAlpha(float alpha_time);

			/*
			*	@param int ms the time in seconds to sleep
			*/
			void sleep(int ms) const;
		};

	}
}

#endif
