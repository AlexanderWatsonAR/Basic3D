#include "stdafx.h"
#include "Input.h"

namespace Basic3D
{
	namespace Input
	{
		MouseState::MouseState()
		{
			leftButton = ButtonState::RELEASED;
			middleButton = ButtonState::RELEASED;
			rightButton = ButtonState::RELEASED;
			scrollWheelValue = 0;
			posX = 0;
			posY = 0;
		}

		KeyArray::KeyArray()
		{
			_keys.fill(Input::KeyState::RELEASED);
		}

		KeyState& KeyArray::operator[] (Keys key)
		{
			return _keys[static_cast<std::size_t>(key)]; // Converts key to index to find the key.
		}

		KeyState KeyArray::operator[] (Keys key) const
		{
			return _keys[static_cast<std::size_t>(key)]; // Converts key to index to find the key.
		}

		bool KeyboardState::IsKeyDown(Keys key)
		{
			return (_keys[key] == KeyState::PRESSED);
		}

		bool KeyboardState::IsKeyUp(Keys key)
		{
			return (_keys[key] == KeyState::RELEASED);
		}

		namespace Mouse
		{
			namespace
			{
				MouseState* mouseState = new MouseState();
			}

			void PassiveMouseMotion(int x, int y)
			{
				mouseState->posX = x;
				mouseState->posY = y;
			}

			void MouseMotion(int x, int y)
			{
				mouseState->posX = x;
				mouseState->posY = y;
			}

			void MouseAction(int button, int state, int x, int y)
			{
				switch (button)
				{
				case GLUT_LEFT_BUTTON:
					if (state == GLUT_UP)
						mouseState->leftButton = ButtonState::RELEASED;
					else
						mouseState->leftButton = ButtonState::PRESSED;
					break;
				case GLUT_MIDDLE_BUTTON:
					if (state == GLUT_UP)
						mouseState->middleButton = ButtonState::RELEASED;
					else
						mouseState->middleButton = ButtonState::PRESSED;
					break;
				case GLUT_RIGHT_BUTTON:
					if (state == GLUT_UP)
						mouseState->rightButton = ButtonState::RELEASED;
					else
						mouseState->rightButton = ButtonState::PRESSED;
					break;
				case 3: //Scroll Up
					if (state != GLUT_UP)
						mouseState->scrollWheelValue++;
					break;
				case 4: //Scroll Down
					if (state != GLUT_UP)
						mouseState->scrollWheelValue--;
					break;
				}

				mouseState->posX = x;
				mouseState->posY = y;
			}

			MouseState * GetState()
			{
				return mouseState;
			}
		}

		namespace Keyboard
		{
			namespace
			{
				KeyboardState * keyboardState = new KeyboardState();
			}

			void KeyboardPressedAction(unsigned char key, int x, int y)
			{
				Keys aKey = Keys::F1;

				switch (key)
				{
				case 'a': case 'A': aKey = Keys::A; break;
				case 'b': case 'B': aKey = Keys::B; break;
				case 'c': case 'C': aKey = Keys::C; break;
				case 'd': case 'D': aKey = Keys::D; break;
				case 'e': case 'E': aKey = Keys::E; break;
				case 'f': case 'F': aKey = Keys::F; break;
				case 'g': case 'G': aKey = Keys::G; break;
				case 'h': case 'H': aKey = Keys::H; break;
				case 'i': case 'I': aKey = Keys::I; break;
				case 'j': case 'J': aKey = Keys::J; break;
				case 'k': case 'K': aKey = Keys::K; break;
				case 'l': case 'L': aKey = Keys::L; break;
				case 'm': case 'M': aKey = Keys::M; break;
				case 'n': case 'N': aKey = Keys::N; break;
				case 'o': case 'O': aKey = Keys::O; break;
				case 'p': case 'P': aKey = Keys::P; break;
				case 'q': case 'Q': aKey = Keys::Q; break;
				case 'r': case 'R': aKey = Keys::R; break;
				case 's': case 'S': aKey = Keys::S; break;
				case 't': case 'T': aKey = Keys::T; break;
				case 'u': case 'U': aKey = Keys::U; break;
				case 'v': case 'V': aKey = Keys::V; break;
				case 'w': case 'W': aKey = Keys::W; break;
				case 'x': case 'X': aKey = Keys::X; break;
				case 'y': case 'Y': aKey = Keys::Y; break;
				case 'z': case 'Z': aKey = Keys::Z; break;
				case '0': aKey = Keys::NUMPAD0; break;
				case '1': aKey = Keys::NUMPAD1; break;
				case '2': aKey = Keys::NUMPAD2; break;
				case '3': aKey = Keys::NUMPAD3; break;
				case '4': aKey = Keys::NUMPAD4; break;
				case '5': aKey = Keys::NUMPAD5; break;
				case '6': aKey = Keys::NUMPAD6; break;
				case '7': aKey = Keys::NUMPAD7; break;
				case '8': aKey = Keys::NUMPAD9; break;
				case '9': aKey = Keys::NUMPAD9; break;
				case '+': aKey = Keys::PLUS; break;
				case '-': aKey = Keys::SUBTRACT; break;
				case '*': aKey = Keys::MULTIPLY; break;
				case '/': aKey = Keys::DIVIDE; break;
				case '.': aKey = Keys::DECIMAL; break;
				case '=': aKey = Keys::EQUALS; break;
				case ' ': aKey = Keys::SPACE; break;
				case '\r': aKey = Keys::RETURN; break;
				case '\t': aKey = Keys::TAB; break;
				case '\b': aKey = Keys::BACKSPACE; break;
				case (char)127: aKey = Keys::DELETE_KEY; break;
				case (char)27: aKey = Keys::ESCAPE; break;
				}

				if (aKey != Keys::F1)
					keyboardState->_keys[aKey] = KeyState::PRESSED;
			}

			void KeyboardReleasedAction(unsigned char key, int x, int y)
			{
				Keys aKey = Keys::F1;

				switch (key)
				{
				case 'a': case 'A': aKey = Keys::A; break;
				case 'b': case 'B': aKey = Keys::B; break;
				case 'c': case 'C': aKey = Keys::C; break;
				case 'd': case 'D': aKey = Keys::D; break;
				case 'e': case 'E': aKey = Keys::E; break;
				case 'f': case 'F': aKey = Keys::F; break;
				case 'g': case 'G': aKey = Keys::G; break;
				case 'h': case 'H': aKey = Keys::H; break;
				case 'i': case 'I': aKey = Keys::I; break;
				case 'j': case 'J': aKey = Keys::J; break;
				case 'k': case 'K': aKey = Keys::K; break;
				case 'l': case 'L': aKey = Keys::L; break;
				case 'm': case 'M': aKey = Keys::M; break;
				case 'n': case 'N': aKey = Keys::N; break;
				case 'o': case 'O': aKey = Keys::O; break;
				case 'p': case 'P': aKey = Keys::P; break;
				case 'q': case 'Q': aKey = Keys::Q; break;
				case 'r': case 'R': aKey = Keys::R; break;
				case 's': case 'S': aKey = Keys::S; break;
				case 't': case 'T': aKey = Keys::T; break;
				case 'u': case 'U': aKey = Keys::U; break;
				case 'v': case 'V': aKey = Keys::V; break;
				case 'w': case 'W': aKey = Keys::W; break;
				case 'x': case 'X': aKey = Keys::X; break;
				case 'y': case 'Y': aKey = Keys::Y; break;
				case 'z': case 'Z': aKey = Keys::Z; break;
				case '0': aKey = Keys::NUMPAD0; break;
				case '1': aKey = Keys::NUMPAD1; break;
				case '2': aKey = Keys::NUMPAD2; break;
				case '3': aKey = Keys::NUMPAD3; break;
				case '4': aKey = Keys::NUMPAD4; break;
				case '5': aKey = Keys::NUMPAD5; break;
				case '6': aKey = Keys::NUMPAD6; break;
				case '7': aKey = Keys::NUMPAD7; break;
				case '8': aKey = Keys::NUMPAD9; break;
				case '9': aKey = Keys::NUMPAD9; break;
				case '+': aKey = Keys::PLUS; break;
				case '-': aKey = Keys::SUBTRACT; break;
				case '*': aKey = Keys::MULTIPLY; break;
				case '/': aKey = Keys::DIVIDE; break;
				case '.': aKey = Keys::DECIMAL; break;
				case '=': aKey = Keys::EQUALS; break;
				case ' ': aKey = Keys::SPACE; break;
				case '\r': aKey = Keys::RETURN; break;
				case '\t': aKey = Keys::TAB; break;
				case '\b': aKey = Keys::BACKSPACE; break;
				case (char)127: aKey = Keys::DELETE_KEY; break;
				case (char)27: aKey = Keys::ESCAPE; break;
				}

				if (aKey != Keys::F1)
					keyboardState->_keys[aKey] = KeyState::RELEASED;
			}

			void KeyboardSpecialPressedAction(int key, int x, int y)
			{
				Keys aKey = Keys::A;

				switch (key)
				{
				case GLUT_KEY_F1: aKey = Keys::F1; break;
				case GLUT_KEY_F2: aKey = Keys::F2; break;
				case GLUT_KEY_F3: aKey = Keys::F3; break;
				case GLUT_KEY_F4: aKey = Keys::F4; break;
				case GLUT_KEY_F5: aKey = Keys::F5; break;
				case GLUT_KEY_F6: aKey = Keys::F6; break;
				case GLUT_KEY_F7: aKey = Keys::F7; break;
				case GLUT_KEY_F8: aKey = Keys::F8; break;
				case GLUT_KEY_F9: aKey = Keys::F9; break;
				case GLUT_KEY_F10: aKey = Keys::F10; break;
				case GLUT_KEY_F11: aKey = Keys::F11; break;
				case GLUT_KEY_F12: aKey = Keys::F12; break;
				case GLUT_KEY_LEFT: aKey = Keys::LEFT; break;
				case GLUT_KEY_UP: aKey = Keys::UP; break;
				case GLUT_KEY_RIGHT: aKey = Keys::RIGHT; break;
				case GLUT_KEY_DOWN: aKey = Keys::DOWN; break;
				case GLUT_KEY_PAGE_UP: aKey = Keys::PAGE_UP; break;
				case GLUT_KEY_PAGE_DOWN: aKey = Keys::PAGE_DOWN; break;
				case GLUT_KEY_HOME: aKey = Keys::HOME; break;
				case GLUT_KEY_END: aKey = Keys::END; break;
				case GLUT_KEY_INSERT: aKey = Keys::INSERT; break;
				case GLUT_KEY_SHIFT_L: aKey = Keys::LEFT_SHIFT; break;
				case GLUT_KEY_SHIFT_R: aKey = Keys::RIGHT_SHIFT; break;
				case GLUT_KEY_ALT_L: aKey = Keys::LEFT_ALT; break;
				case GLUT_KEY_ALT_R: aKey = Keys::RIGHT_ALT; break;
				case GLUT_KEY_CTRL_L: aKey = Keys::LEFT_CONTROL; break;
				case GLUT_KEY_CTRL_R: aKey = Keys::RIGHT_CONTROL; break;
				}

				if (aKey != Keys::A)
					keyboardState->_keys[aKey] = KeyState::PRESSED;
			}

			void KeyboardSpecialReleasedAction(int key, int x, int y)
			{
				Keys aKey = Keys::A;

				switch (key)
				{
				case GLUT_KEY_F1: aKey = Keys::F1; break;
				case GLUT_KEY_F2: aKey = Keys::F2; break;
				case GLUT_KEY_F3: aKey = Keys::F3; break;
				case GLUT_KEY_F4: aKey = Keys::F4; break;
				case GLUT_KEY_F5: aKey = Keys::F5; break;
				case GLUT_KEY_F6: aKey = Keys::F6; break;
				case GLUT_KEY_F7: aKey = Keys::F7; break;
				case GLUT_KEY_F8: aKey = Keys::F8; break;
				case GLUT_KEY_F9: aKey = Keys::F9; break;
				case GLUT_KEY_F10: aKey = Keys::F10; break;
				case GLUT_KEY_F11: aKey = Keys::F11; break;
				case GLUT_KEY_F12: aKey = Keys::F12; break;
				case GLUT_KEY_LEFT: aKey = Keys::LEFT; break;
				case GLUT_KEY_UP: aKey = Keys::UP; break;
				case GLUT_KEY_RIGHT: aKey = Keys::RIGHT; break;
				case GLUT_KEY_DOWN: aKey = Keys::DOWN; break;
				case GLUT_KEY_PAGE_UP: aKey = Keys::PAGE_UP; break;
				case GLUT_KEY_PAGE_DOWN: aKey = Keys::PAGE_DOWN; break;
				case GLUT_KEY_HOME: aKey = Keys::HOME; break;
				case GLUT_KEY_END: aKey = Keys::END; break;
				case GLUT_KEY_INSERT: aKey = Keys::INSERT; break;
				case GLUT_KEY_SHIFT_L: aKey = Keys::LEFT_SHIFT; break;
				case GLUT_KEY_SHIFT_R: aKey = Keys::RIGHT_SHIFT; break;
				case GLUT_KEY_ALT_L: aKey = Keys::LEFT_ALT; break;
				case GLUT_KEY_ALT_R: aKey = Keys::RIGHT_ALT; break;
				case GLUT_KEY_CTRL_L: aKey = Keys::LEFT_CONTROL; break;
				case GLUT_KEY_CTRL_R: aKey = Keys::RIGHT_CONTROL; break;
				}

				if (aKey != Keys::A)
					keyboardState->_keys[aKey] = KeyState::RELEASED;
			}

			KeyboardState * GetState()
			{
				return keyboardState;
			}
		}

		void Initialise()
		{
			glutPassiveMotionFunc(Mouse::PassiveMouseMotion);
			glutMotionFunc(Mouse::MouseMotion);
			glutMouseFunc(Mouse::MouseAction);
			glutKeyboardFunc(Keyboard::KeyboardPressedAction);
			glutKeyboardUpFunc(Keyboard::KeyboardReleasedAction);
			glutSpecialFunc(Keyboard::KeyboardSpecialPressedAction);
			glutSpecialUpFunc(Keyboard::KeyboardSpecialReleasedAction);
		}

		void Destroy()
		{
			glutPassiveMotionFunc(nullptr);
			glutMotionFunc(nullptr);
			glutMouseFunc(nullptr);
			glutKeyboardFunc(nullptr);
			glutKeyboardUpFunc(nullptr);
			glutSpecialFunc(nullptr);
			glutSpecialUpFunc(nullptr);
		}
	}
}
