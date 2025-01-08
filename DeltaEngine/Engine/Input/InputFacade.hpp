#pragma once

#include "SDL.h"

#include <iostream>
#include <vector>

#include "InputManager.hpp"
#include "DeltaInputs.hpp"

class InputFacade
{
public:
	InputFacade();

	bool isInputEvent(SDL_Event event);
	void onInputEvent(SDL_Event event);

	void onKeyDown(SDL_Event event);
	void onKeyUp(SDL_Event event);

	void onMouseMove(SDL_Event event);
	void onMouseButtonDown(SDL_Event event);
	void onMouseButtonUp(SDL_Event event);
	void onMouseScroll(SDL_Event event);

private:
	InputManager& inputManager;

	const std::vector<SDL_EventType> inputTypes
	{
		SDL_KEYDOWN, 
		SDL_KEYUP, 
		SDL_MOUSEBUTTONDOWN, 
		SDL_MOUSEBUTTONUP, 
		SDL_MOUSEMOTION, 
		SDL_MOUSEWHEEL
	};

	const std::unordered_map<SDL_Keycode, Key> SDLToDeltaKeys = 
	{
		// Alphabet keys
		{SDLK_a, KEY_A},
		{SDLK_b, KEY_B},
		{SDLK_c, KEY_C},
		{SDLK_d, KEY_D},
		{SDLK_e, KEY_E},
		{SDLK_f, KEY_F},
		{SDLK_g, KEY_G},
		{SDLK_h, KEY_H},
		{SDLK_i, KEY_I},
		{SDLK_j, KEY_J},
		{SDLK_k, KEY_K},
		{SDLK_l, KEY_L},
		{SDLK_m, KEY_M},
		{SDLK_n, KEY_N},
		{SDLK_o, KEY_O},
		{SDLK_p, KEY_P},
		{SDLK_q, KEY_Q},
		{SDLK_r, KEY_R},
		{SDLK_s, KEY_S},
		{SDLK_t, KEY_T},
		{SDLK_u, KEY_U},
		{SDLK_v, KEY_V},
		{SDLK_w, KEY_W},
		{SDLK_x, KEY_X},
		{SDLK_y, KEY_Y},
		{SDLK_z, KEY_Z},

		// Number keys
		{SDLK_0, KEY_0},
		{SDLK_1, KEY_1},
		{SDLK_2, KEY_2},
		{SDLK_3, KEY_3},
		{SDLK_4, KEY_4},
		{SDLK_5, KEY_5},
		{SDLK_6, KEY_6},
		{SDLK_7, KEY_7},
		{SDLK_8, KEY_8},
		{SDLK_9, KEY_9},

		// Function keys
		{SDLK_F1, KEY_F1},
		{SDLK_F2, KEY_F2},
		{SDLK_F3, KEY_F3},
		{SDLK_F4, KEY_F4},
		{SDLK_F5, KEY_F5},
		{SDLK_F6, KEY_F6},
		{SDLK_F7, KEY_F7},
		{SDLK_F8, KEY_F8},
		{SDLK_F9, KEY_F9},
		{SDLK_F10, KEY_F10},
		{SDLK_F11, KEY_F11},
		{SDLK_F12, KEY_F12},

		// Arrow keys
		{SDLK_UP, KEY_UP},
		{SDLK_DOWN, KEY_DOWN},
		{SDLK_LEFT, KEY_LEFT},
		{SDLK_RIGHT, KEY_RIGHT},

		// Modifier keys
		{SDLK_LSHIFT, KEY_LSHIFT},
		{SDLK_RSHIFT, KEY_RSHIFT},
		{SDLK_LCTRL, KEY_LCTRL},
		{SDLK_RCTRL, KEY_RCTRL},
		{SDLK_LALT, KEY_LALT},
		{SDLK_RALT, KEY_RALT},

		// Special keys
		{SDLK_TAB, KEY_TAB},
		{SDLK_CAPSLOCK, KEY_CAPSLOCK},
		{SDLK_BACKSPACE, KEY_BACKSPACE},
		{SDLK_RETURN, KEY_ENTER},
		{SDLK_ESCAPE, KEY_ESCAPE},
		{SDLK_SPACE, KEY_SPACE},
		{SDLK_DELETE, KEY_DELETE},
		{SDLK_HOME, KEY_HOME},
		{SDLK_END, KEY_END},
		{SDLK_PAGEUP, KEY_PAGEUP},
		{SDLK_PAGEDOWN, KEY_PAGEDOWN},
		{SDLK_INSERT, KEY_INSERT},

		// Symbol keys
		{SDLK_COMMA, KEY_COMMA},
		{SDLK_PERIOD, KEY_PERIOD},
		{SDLK_SLASH, KEY_SLASH},
		{SDLK_SEMICOLON, KEY_SEMICOLON},
		{SDLK_QUOTE, KEY_APOSTROPHE},
		{SDLK_LEFTBRACKET, KEY_LEFTBRACKET},
		{SDLK_RIGHTBRACKET, KEY_RIGHTBRACKET},
		{SDLK_BACKSLASH, KEY_BACKSLASH},
		{SDLK_MINUS, KEY_MINUS},
		{SDLK_EQUALS, KEY_EQUALS},
		{SDLK_BACKQUOTE, KEY_GRAVE},

		// Keypad (numpad) keys
		{SDLK_KP_0, KEY_KP_0},
		{SDLK_KP_1, KEY_KP_1},
		{SDLK_KP_2, KEY_KP_2},
		{SDLK_KP_3, KEY_KP_3},
		{SDLK_KP_4, KEY_KP_4},
		{SDLK_KP_5, KEY_KP_5},
		{SDLK_KP_6, KEY_KP_6},
		{SDLK_KP_7, KEY_KP_7},
		{SDLK_KP_8, KEY_KP_8},
		{SDLK_KP_9, KEY_KP_9},
		{SDLK_KP_DIVIDE, KEY_KP_DIVIDE},
		{SDLK_KP_MULTIPLY, KEY_KP_MULTIPLY},
		{SDLK_KP_MINUS, KEY_KP_MINUS},
		{SDLK_KP_PLUS, KEY_KP_PLUS},
		{SDLK_KP_ENTER, KEY_KP_ENTER},
		{SDLK_KP_PERIOD, KEY_KP_PERIOD},

		// Miscellaneous keys
		{SDLK_PRINTSCREEN, KEY_PRINTSCREEN},
		{SDLK_SCROLLLOCK, KEY_SCROLLLOCK},
		{SDLK_PAUSE, KEY_PAUSE}
	};
};
