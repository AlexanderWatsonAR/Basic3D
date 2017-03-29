#pragma once
#include "Basic3D.h"
#include <array>
#include <vector>

namespace Basic3D
{
	namespace Input
	{
		void BASIC3D_API Initialise();
		void BASIC3D_API Destroy();

		enum class BASIC3D_API ButtonState
		{
			RELEASED = 0,
			PRESSED
		};

		enum class BASIC3D_API KeyState
		{
			RELEASED = 0,
			PRESSED
		};

		enum class BASIC3D_API Keys
		{
			A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			UP, DOWN, LEFT, RIGHT, BACK, HOME, END, PAGE_UP, PAGE_DOWN,
			INSERT, DELETE_KEY, RETURN, BACKSPACE, TAB, ESCAPE,
			SPACE, PLUS, SUBTRACT, MULTIPLY, DIVIDE, DECIMAL, EQUALS,
			LEFT_CONTROL, LEFT_ALT, LEFT_SHIFT, RIGHT_CONTROL, RIGHT_ALT, RIGHT_SHIFT,
			NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
			COUNT
		};

		class BASIC3D_API KeyArray
		{
		public:
			KeyArray();
			KeyState& operator[] (Keys key);
			KeyState operator[] (Keys key) const;
		private:
			std::array<KeyState, static_cast< std::size_t >(Keys::COUNT)> _keys;
		};

		class BASIC3D_API KeyboardState
		{
		public:
			KeyArray _keys;

			KeyboardState() {}
			bool IsKeyDown(Keys key);
			bool IsKeyUp(Keys key);
		};

		class BASIC3D_API MouseState
		{
		public:
			ButtonState leftButton;
			ButtonState middleButton;
			ButtonState rightButton;
			int scrollWheelValue;
			int posX;
			int posY;
			MouseState();
		};

		namespace Keyboard
		{
			BASIC3D_API KeyboardState * GetState();
		}

		namespace Mouse
		{
			BASIC3D_API MouseState * GetState();
		}
	}
}
