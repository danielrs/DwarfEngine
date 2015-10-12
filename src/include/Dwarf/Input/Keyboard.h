
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../DwarfSetup.h"
#include "KeyboardProvider.h"
#include "KeyboardListener.h"

/**
 *	Service locator for KeyboardProvider
 */

namespace Dwarf
{
	namespace Input
	{

		class DWARFAPI Keyboard
		{
		private:
			static KeyboardProvider* _service;
			static KeyboardListener* _keyboard_listener;

		public:
			static const KeyboardProvider& get();
			static void set(KeyboardProvider* service);
			static void setKeyboardListener(KeyboardListener* keyboard_listener);
			static KeyboardListener* getKeyboardListener();

			// This methods are used to mirror
			// the service virtual methods
			static bool isKeyDown(const Keycode &key);
			static void keyPressed(const Keycode &key);
			static void keyReleased(const Keycode &key);
		};

	}
}

#endif
