#include <Dwarf/Input/Keyboard.h>
#include <Dwarf/Input/GLFWKeyboard.h>

#include <iostream>
using namespace std;

namespace Dwarf
{
	namespace Input
	{

		KeyboardProvider* Keyboard::_service = nullptr;
		KeyboardListener* Keyboard::_keyboard_listener = nullptr;

		// ----------------------------------------------------------------

		const KeyboardProvider& Keyboard::get()
		{
			if (!_service) set(new GLFWKeyboard);
			return *_service;
		}

		// ----------------------------------------------------------------

		void Keyboard::set(KeyboardProvider* service)
		{
			if (_service) delete _service;
			_service = service;
		}

		// --------------------------------

		void Keyboard::setKeyboardListener(KeyboardListener *keyboard_listener) {
			_keyboard_listener = keyboard_listener;
		}

		// --------------------------------

		KeyboardListener* Keyboard::getKeyboardListener() {
			return _keyboard_listener;
		}

		// ----------------------------------------------------------------

		bool Keyboard::isKeyDown(const Keycode &key)
		{
			if (!_service) set(new GLFWKeyboard);
			return _service->isKeyDown(key);
		}

		// ----------------------------------------------------------------

		void Keyboard::keyPressed(const Keycode &key)
		{
			if (!_service) set(new GLFWKeyboard);
			_service->keyPressed(key);

			if(_keyboard_listener) _keyboard_listener->onKeyPressed(key);
		}

		// ----------------------------------------------------------------

		void Keyboard::keyReleased(const Keycode &key)
		{
			if (!_service) set(new GLFWKeyboard);
			_service->keyReleased(key);

			if(_keyboard_listener) _keyboard_listener->onKeyReleased(key);
		}

	}
}
