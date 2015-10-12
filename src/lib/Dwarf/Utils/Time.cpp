#include <Dwarf/Util/Time.h>
#include <ctime>

#ifdef _WIN32
#include <Windows.h>
#elif defined(__APPLE__) || defined(__linux)
#include <ctime>
#include <thread>
#endif

using namespace std;

namespace Dwarf
{
	namespace Util
	{
		/**
		 * Instantiates the singleton at compile time (required for DLL)
		 */
		 #ifndef DWARF_STATIC
		void instantiate_time()
		{
			Singleton<Time>::INSTANCE();
			Time::INSTANCE().fixed_step = 1/60.0f;
		}
		#endif // DWARF_STATIC

		void Time::initialize()
		{
			#ifdef _WIN32
			QueryPerformanceFrequency(&CLOCK_FREQUENCY);
			QueryPerformanceCounter(&START_STEP);
			last_step = START_STEP;
			#elif defined(__APPLE__) || defined(__linux)
			START_STEP = std::chrono::high_resolution_clock::now();
			last_step = START_STEP;
			#endif

			fixed_step = 1/60.0f;
		}


		// ----------------------------------------------------------------

		void Time::step()
		{
			#ifdef _WIN32
			LARGE_INTEGER curr_step;
			QueryPerformanceCounter(&curr_step);
			delta_time = (float)((curr_step.QuadPart - last_step.QuadPart) / (double) CLOCK_FREQUENCY.QuadPart);
			#elif defined(__APPLE__) || defined(__linux)
			std::chrono::time_point<std::chrono::high_resolution_clock> curr_step =
				std::chrono::high_resolution_clock::now();
			delta_time = std::chrono::duration_cast<std::chrono::microseconds>(curr_step - last_step).count()/1000000.0f;
			#endif

			last_step = curr_step;
		}

		// ----------------------------------------------------------------

		float Time::current() const
		{
			#ifdef _WIN32
			LARGE_INTEGER curr_step;
			QueryPerformanceCounter(&curr_step);
			return (float)((curr_step.QuadPart - START_STEP.QuadPart) / (double) CLOCK_FREQUENCY.QuadPart);
			#elif defined(__APPLE__) || defined(__linux)
			std::chrono::time_point<std::chrono::high_resolution_clock> curr_step =
				std::chrono::high_resolution_clock::now();
				return std::chrono::duration_cast<std::chrono::microseconds>(curr_step - START_STEP).count()/1000000.0f;
			#endif
		}

		// ----------------------------------------------------------------

		float Time::delta() const
		{
			return delta_time;
		}

		// ----------------------------------------------------------------

		float Time::alpha() const
		{
			/*
			*	The main Gameloop (in DwarfRoot.h & DwarfRoot.cpp) uses
			*	a fixed Timestep for fixedUpdate() and dynamic timestep
			*	for common update() and render() methods.
			*
			*	Alpha time is the accumulator time that couldn't be used
			*	in the frame, hence desynchronizing the render() with the
			*	simulation (fixedUpdate())
			*/

			return alpha_time;
		}

		// ----------------------------------------------------------------

		void Time::setAlpha(float alpha_time)
		{
			this->alpha_time = alpha_time;
		}

		// ----------------------------------------------------------------

		void Time::sleep(int ms) const
		{
			#ifdef _WIN32
			SleepEx(ms, false);
			#elif defined(__APPLE__) || defined(__linux)
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
			#endif
		}
	} // end of namespace Util
} // end of namespace Dwarf
