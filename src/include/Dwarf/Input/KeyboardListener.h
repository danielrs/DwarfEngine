#ifndef DWARF_INPUT_KEYBOARD_LISTENER_H
#define DWARF_INPUT_KEYBOARD_LISTENER_H

#include "../DwarfSetup.h"
#include "KeyboardDef.h"

namespace Dwarf {
	namespace Input {

		class DWARFAPI KeyboardListener {
		public:
			virtual void onKeyPressed(const Keycode &key) = 0;
			virtual void onKeyReleased(const Keycode &key) = 0;
		};
	}
}

#endif
