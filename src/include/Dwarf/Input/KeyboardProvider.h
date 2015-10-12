#ifndef IKEYBOARD_H
#define IKEYBOARD_H

#include "../DwarfSetup.h"
#include "KeyboardDef.h"

#include <vector>

/**
 * KeyboardProvider interface
 */

namespace Dwarf
{
	namespace Input
	{

		class DWARFAPI KeyboardProvider {
		public:
			virtual ~KeyboardProvider();
			virtual bool isKeyDown(const Keycode &code) const = 0;
			virtual void keyPressed(const Keycode &code) = 0;
			virtual void keyReleased(const Keycode &code) = 0;
			virtual std::vector<Keycode> getPressedKeys() const = 0;
			/**
			 * NOTE
			 * Since we will have multiple service providers that may or may not
			 * use the same keycodes that the engine uses we need a way to translate
			 * the key codes of 3rd party libraries. This funcion does just that.
			 * P.S. GLFWKeyboard only translates GLFW codes, SDLKeyboard only SDL codes
			 * and so on.
			 * @param code the code to be translated (used by 3rd party library)
			 * @return code equivalent in Keycode terms
			 */
			virtual Keycode translate(const int &code) const = 0;

		};

	}
}

#endif
