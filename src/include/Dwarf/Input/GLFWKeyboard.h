#ifndef DWARF_INPUT_GLFWKEYBOARD_H
#define DWARF_INPUT_GLFWKEYBOARD_H

#include "../DwarfSetup.h"
#include "KeyboardProvider.h"
#include "KeyboardDef.h"

#include <map>
#include <set>

/**
 * Keyboard service provider
 */

namespace Dwarf
{
	namespace Input
	{

		class DWARFAPI GLFWKeyboard : public KeyboardProvider
		{
		private:
			// Contains translations from GLFW_KEY definitions to Keycode enum
			static std::map<int, Keycode> _key_translation;
			std::set<Keycode> _pressed_keys;

		public:
			virtual bool isKeyDown(const Keycode &code) const;
			virtual void keyPressed(const Keycode &code);
			virtual void keyReleased(const Keycode &code);
			virtual std::vector<Keycode> getPressedKeys() const;
			virtual Keycode translate(const int &code) const;
		};
	}
}

#endif // GLFWKEYBOARD_H
