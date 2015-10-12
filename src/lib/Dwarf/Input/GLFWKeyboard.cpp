#include <Dwarf/Input/GLFWKeyboard.h>
#include <GLFW/glfw3.h>

#include <map>
#include <set>

using namespace std;

namespace Dwarf
{
	namespace Input
	{
		bool GLFWKeyboard::isKeyDown(const Keycode &code) const
		{
			return _pressed_keys.find(code) != _pressed_keys.end();
		}

		// ----------------------------------------------------------------

		void GLFWKeyboard::keyPressed(const Keycode &code)
		{
			_pressed_keys.insert(code);
		}

		// ----------------------------------------------------------------

		void GLFWKeyboard::keyReleased(const Keycode &code)
		{
			_pressed_keys.erase(code);
		}

		// --------------------------------

		vector<Keycode> GLFWKeyboard::getPressedKeys() const {
			
			vector<Keycode> pressed_keys;
			for (auto it = _pressed_keys.begin(); it != _pressed_keys.end(); ++it) {
				pressed_keys.push_back(*it);
			}
			
			return pressed_keys;
		}

		// ----------------------------------------------------------------

		Keycode GLFWKeyboard::translate(const int &code) const
		{
			map<int, Keycode>::iterator code_translation = _key_translation.find(code);
			if (code_translation != _key_translation.end())
				return code_translation->second;

			return Keycode::UNKNOWN;
		}

		// ----------------------------------------------------------------

		map<int, Keycode> GLFWKeyboard::_key_translation = {
			{GLFW_KEY_UNKNOWN, Keycode::UNKNOWN},
			{GLFW_KEY_BACKSPACE, Keycode::BACKSPACE},
			{GLFW_KEY_DELETE, Keycode::DELETE},
			{GLFW_KEY_TAB, Keycode::TAB},
			{GLFW_KEY_ENTER, Keycode::RETURN},
			{GLFW_KEY_PAUSE, Keycode::PAUSE},
			{GLFW_KEY_ESCAPE, Keycode::ESCAPE},
			{GLFW_KEY_SPACE, Keycode::SPACE},
			{GLFW_KEY_KP_0, Keycode::KEYPAD0},
			{GLFW_KEY_KP_1, Keycode::KEYPAD1},
			{GLFW_KEY_KP_2, Keycode::KEYPAD2},
			{GLFW_KEY_KP_3, Keycode::KEYPAD3},
			{GLFW_KEY_KP_4, Keycode::KEYPAD4},
			{GLFW_KEY_KP_5, Keycode::KEYPAD5},
			{GLFW_KEY_KP_6, Keycode::KEYPAD6},
			{GLFW_KEY_KP_7, Keycode::KEYPAD7},
			{GLFW_KEY_KP_8, Keycode::KEYPAD8},
			{GLFW_KEY_KP_9, Keycode::KEYPAD9},
			{GLFW_KEY_KP_DECIMAL, Keycode::KEYPAD_PERIOD},
			{GLFW_KEY_KP_DIVIDE, Keycode::KEYPAD_DIVIDE},
			{GLFW_KEY_KP_MULTIPLY, Keycode::KEYPAD_MULTIPLY},
			{GLFW_KEY_KP_SUBTRACT, Keycode::KEYPAD_MINUS},
			{GLFW_KEY_KP_ADD, Keycode::KEYPAD_PLUS},
			{GLFW_KEY_KP_ENTER, Keycode::KEYPAD_ENTER},
			{GLFW_KEY_KP_EQUAL, Keycode::KEYPAD_EQUALS},
			{GLFW_KEY_UP, Keycode::UP},
			{GLFW_KEY_DOWN, Keycode::DOWN},
			{GLFW_KEY_LEFT, Keycode::LEFT},
			{GLFW_KEY_RIGHT, Keycode::RIGHT},
			{GLFW_KEY_INSERT, Keycode::INSERT},
			{GLFW_KEY_HOME, Keycode::HOME},
			{GLFW_KEY_END, Keycode::END},
			{GLFW_KEY_PAGE_UP, Keycode::PAGE_UP},
			{GLFW_KEY_PAGE_DOWN, Keycode::PAGE_DOWN},
			{GLFW_KEY_F1, Keycode::F1},
			{GLFW_KEY_F2, Keycode::F2},
			{GLFW_KEY_F3, Keycode::F3},
			{GLFW_KEY_F4, Keycode::F4},
			{GLFW_KEY_F5, Keycode::F5},
			{GLFW_KEY_F6, Keycode::F6},
			{GLFW_KEY_F7, Keycode::F7},
			{GLFW_KEY_F8, Keycode::F8},
			{GLFW_KEY_F9, Keycode::F9},
			{GLFW_KEY_F10, Keycode::F10},
			{GLFW_KEY_F11, Keycode::F11},
			{GLFW_KEY_F12, Keycode::F12},
			{GLFW_KEY_F13, Keycode::F13},
			{GLFW_KEY_F14, Keycode::F14},
			{GLFW_KEY_F15, Keycode::F15},
			{GLFW_KEY_0, Keycode::NUM0},
			{GLFW_KEY_1, Keycode::NUM1},
			{GLFW_KEY_2, Keycode::NUM2},
			{GLFW_KEY_3, Keycode::NUM3},
			{GLFW_KEY_4, Keycode::NUM4},
			{GLFW_KEY_5, Keycode::NUM5},
			{GLFW_KEY_6, Keycode::NUM6},
			{GLFW_KEY_7, Keycode::NUM7},
			{GLFW_KEY_8, Keycode::NUM8},
			{GLFW_KEY_9, Keycode::NUM9},
			{GLFW_KEY_UNKNOWN, Keycode::EXCLAIM},
			{GLFW_KEY_UNKNOWN, Keycode::DOUBLE_QUOTE},
			{GLFW_KEY_UNKNOWN, Keycode::HASH},
			{GLFW_KEY_UNKNOWN, Keycode::DOLLAR},
			{GLFW_KEY_UNKNOWN, Keycode::AMPERSAND},
			{GLFW_KEY_APOSTROPHE, Keycode::QUOTE},
			{GLFW_KEY_UNKNOWN, Keycode::LEFT_PAREN},
			{GLFW_KEY_UNKNOWN, Keycode::RIGHT_PAREN},
			{GLFW_KEY_UNKNOWN, Keycode::ASTERISK},
			{GLFW_KEY_UNKNOWN, Keycode::PLUS},
			{GLFW_KEY_COMMA, Keycode::COMMA},
			{GLFW_KEY_MINUS, Keycode::MINUS},
			{GLFW_KEY_PERIOD, Keycode::PERIOD},
			{GLFW_KEY_SLASH, Keycode::SLASH},
			{GLFW_KEY_UNKNOWN, Keycode::COLON},
			{GLFW_KEY_SEMICOLON, Keycode::SEMICOLON},
			{GLFW_KEY_UNKNOWN, Keycode::LESS},
			{GLFW_KEY_EQUAL, Keycode::EQUALS},
			{GLFW_KEY_UNKNOWN, Keycode::GREATER},
			{GLFW_KEY_UNKNOWN, Keycode::QUESTION},
			{GLFW_KEY_UNKNOWN, Keycode::AT},
			{GLFW_KEY_LEFT_BRACKET, Keycode::LEFT_BRACKET},
			{GLFW_KEY_BACKSLASH, Keycode::BACKSLASH},
			{GLFW_KEY_RIGHT_BRACKET, Keycode::RIGHT_BRACKET},
			{GLFW_KEY_UNKNOWN, Keycode::CARET},
			{GLFW_KEY_UNKNOWN, Keycode::UNDERSCORE},
			{GLFW_KEY_UNKNOWN, Keycode::BACKQUOTE},
			{GLFW_KEY_A, Keycode::A},
			{GLFW_KEY_B, Keycode::B},
			{GLFW_KEY_C, Keycode::C},
			{GLFW_KEY_D, Keycode::D},
			{GLFW_KEY_E, Keycode::E},
			{GLFW_KEY_F, Keycode::F},
			{GLFW_KEY_G, Keycode::G},
			{GLFW_KEY_H, Keycode::H},
			{GLFW_KEY_I, Keycode::I},
			{GLFW_KEY_J, Keycode::J},
			{GLFW_KEY_K, Keycode::K},
			{GLFW_KEY_L, Keycode::L},
			{GLFW_KEY_M, Keycode::M},
			{GLFW_KEY_N, Keycode::N},
			{GLFW_KEY_O, Keycode::O},
			{GLFW_KEY_P, Keycode::P},
			{GLFW_KEY_Q, Keycode::Q},
			{GLFW_KEY_R, Keycode::R},
			{GLFW_KEY_S, Keycode::S},
			{GLFW_KEY_T, Keycode::T},
			{GLFW_KEY_U, Keycode::U},
			{GLFW_KEY_V, Keycode::V},
			{GLFW_KEY_W, Keycode::W},
			{GLFW_KEY_X, Keycode::X},
			{GLFW_KEY_Y, Keycode::Y},
			{GLFW_KEY_Z, Keycode::Z},
			{GLFW_KEY_NUM_LOCK, Keycode::NUMLOCK},
			{GLFW_KEY_CAPS_LOCK, Keycode::CAPSLOCK},
			{GLFW_KEY_SCROLL_LOCK, Keycode::SCROLLLOCK},
			{GLFW_KEY_LEFT_SHIFT, Keycode::LEFT_SHIFT},
			{GLFW_KEY_LEFT_CONTROL, Keycode::LEFT_CONTROL},
			{GLFW_KEY_LEFT_ALT, Keycode::LEFT_ALT},
			{GLFW_KEY_LEFT_SUPER, Keycode::LEFT_SUPER},
			{GLFW_KEY_RIGHT_SHIFT, Keycode::RIGHT_SHIFT},
			{GLFW_KEY_RIGHT_CONTROL, Keycode::RIGHT_CONTROL},
			{GLFW_KEY_RIGHT_ALT, Keycode::RIGHT_ALT},
			{GLFW_KEY_RIGHT_SUPER, Keycode::RIGHT_SUPER},
			{GLFW_KEY_PRINT_SCREEN, Keycode::PRINT},
			{GLFW_KEY_UNKNOWN, Keycode::BREAK},
			{GLFW_KEY_MENU, Keycode::MENU}
		};
	}
}
