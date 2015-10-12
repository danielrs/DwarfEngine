#ifndef DWARF_GRAPHICS_WINDOW_H
#define DWARF_GRAPHICS_WINDOW_H

#include "../DwarfSetup.h"
#include <string>

namespace Dwarf
{
	namespace Graphics
	{

		class DWARFAPI Window
		{
		public:
			virtual ~Window();

			virtual bool initialize() = 0;
			virtual void destroy() = 0;

			virtual void setTitle(const std::string &title) = 0;
			virtual void setSize(const size_t &width, const size_t &height) = 0;

			virtual std::string getTitle() const = 0;
			virtual int getWidth() const = 0;
			virtual int getHeight() const = 0;
			virtual float getAspect() const = 0;

			// Updates the events for this window
			virtual void updateEvents() = 0;

			// GL related
			// Makes the OpenGL context of this window current
			virtual void makeContextCurrent() = 0;
			// Swap buffers (double buffering should always be used)
			virtual void swapBuffers() = 0;
			// VSYNC disable-enable
			virtual void useVSync(bool active) = 0;

			// Signals the window to quit
			virtual void quit() = 0;
			// true if the window was signaled to quit
			virtual bool shouldQuit() = 0;

		};
	}
}
#endif
