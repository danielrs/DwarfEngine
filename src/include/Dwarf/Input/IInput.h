#ifndef IINPUT_H
#define IINPUT_H

/*
	Inteface for Input handlers,
	These input handlers should take care of things like:

	Window's Quit event
	Keyboard events
	Mouse events
	Joystick events
*/

#include "../DwarfSetup.h"
#include "../Graphics/Window.h"

namespace Dwarf
{
	namespace Input
	{

		class DWARFAPI IInput
		{
		public:
			virtual ~IInput();
			/*
			Updates the events for Keyboard, Mouse and Joystick
			@param window to which report a quit event
			*/
			virtual void update(Graphics::Window* window) = 0;
		};
	}
}

#endif
