#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>
#include "InputManager.hpp"
#include "InputsEnum.hpp"

class InputFacade
{
public:
	InputFacade();

	bool isInputEvent(SDL_Event event);

	void onInputEvent(SDL_Event event);

	KeyListener makeKeyStruct(SDL_Event event);
	MouseListener makeMouseStruct(SDL_Event event);

	void onKeyDown(SDL_Event event);
	void onKeyUp(SDL_Event event);
	void onMouseMove(SDL_Event event);
	void onMouseButtonDown(SDL_Event event);
	void onMouseButtonUp(SDL_Event event);
	void onMouseScroll(SDL_Event event);

private:
	InputManager& inputManager;

	const std::vector<SDL_EventType> inputTypes{
		SDL_KEYDOWN, SDL_KEYUP, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP, SDL_MOUSEMOTION, SDL_MOUSEWHEEL};

	const std::unordered_map<Key, SDL_KeyCode> keyToSDL = {
		// Alphabet keys
		{KEY_A, SDLK_a},
		{KEY_B, SDLK_b},
		{KEY_C, SDLK_c},
		{KEY_D, SDLK_d},
		{KEY_E, SDLK_e},
		{KEY_F, SDLK_f},
		{KEY_G, SDLK_g},
		{KEY_H, SDLK_h},
		{KEY_I, SDLK_i},
		{KEY_J, SDLK_j},
		{KEY_K, SDLK_k},
		{KEY_L, SDLK_l},
		{KEY_M, SDLK_m},
		{KEY_N, SDLK_n},
		{KEY_O, SDLK_o},
		{KEY_P, SDLK_p},
		{KEY_Q, SDLK_q},
		{KEY_R, SDLK_r},
		{KEY_S, SDLK_s},
		{KEY_T, SDLK_t},
		{KEY_U, SDLK_u},
		{KEY_V, SDLK_v},
		{KEY_W, SDLK_w},
		{KEY_X, SDLK_x},
		{KEY_Y, SDLK_y},
		{KEY_Z, SDLK_z},

		// Number keys
		{KEY_0, SDLK_0},
		{KEY_1, SDLK_1},
		{KEY_2, SDLK_2},
		{KEY_3, SDLK_3},
		{KEY_4, SDLK_4},
		{KEY_5, SDLK_5},
		{KEY_6, SDLK_6},
		{KEY_7, SDLK_7},
		{KEY_8, SDLK_8},
		{KEY_9, SDLK_9},

		// Function keys
		{KEY_F1, SDLK_F1},
		{KEY_F2, SDLK_F2},
		{KEY_F3, SDLK_F3},
		{KEY_F4, SDLK_F4},
		{KEY_F5, SDLK_F5},
		{KEY_F6, SDLK_F6},
		{KEY_F7, SDLK_F7},
		{KEY_F8, SDLK_F8},
		{KEY_F9, SDLK_F9},
		{KEY_F10, SDLK_F10},
		{KEY_F11, SDLK_F11},
		{KEY_F12, SDLK_F12},

		// Arrow keys
		{KEY_UP, SDLK_UP},
		{KEY_DOWN, SDLK_DOWN},
		{KEY_LEFT, SDLK_LEFT},
		{KEY_RIGHT, SDLK_RIGHT},

		// Modifier keys
		{KEY_LSHIFT, SDLK_LSHIFT},
		{KEY_RSHIFT, SDLK_RSHIFT},
		{KEY_LCTRL, SDLK_LCTRL},
		{KEY_RCTRL, SDLK_RCTRL},
		{KEY_LALT, SDLK_LALT},
		{KEY_RALT, SDLK_RALT},

		// Special keys
		{KEY_TAB, SDLK_TAB},
		{KEY_CAPSLOCK, SDLK_CAPSLOCK},
		{KEY_BACKSPACE, SDLK_BACKSPACE},
		{KEY_ENTER, SDLK_RETURN},
		{KEY_ESCAPE, SDLK_ESCAPE},
		{KEY_SPACE, SDLK_SPACE},
		{KEY_DELETE, SDLK_DELETE},
		{KEY_HOME, SDLK_HOME},
		{KEY_END, SDLK_END},
		{KEY_PAGEUP, SDLK_PAGEUP},
		{KEY_PAGEDOWN, SDLK_PAGEDOWN},
		{KEY_INSERT, SDLK_INSERT},

		// Symbol keys
		{KEY_COMMA, SDLK_COMMA},
		{KEY_PERIOD, SDLK_PERIOD},
		{KEY_SLASH, SDLK_SLASH},
		{KEY_SEMICOLON, SDLK_SEMICOLON},
		{KEY_APOSTROPHE, SDLK_QUOTE},
		{KEY_LEFTBRACKET, SDLK_LEFTBRACKET},
		{KEY_RIGHTBRACKET, SDLK_RIGHTBRACKET},
		{KEY_BACKSLASH, SDLK_BACKSLASH},
		{KEY_MINUS, SDLK_MINUS},
		{KEY_EQUALS, SDLK_EQUALS},
		{KEY_GRAVE, SDLK_BACKQUOTE},

		// Keypad (numpad) keys
		{KEY_KP_0, SDLK_KP_0},
		{KEY_KP_1, SDLK_KP_1},
		{KEY_KP_2, SDLK_KP_2},
		{KEY_KP_3, SDLK_KP_3},
		{KEY_KP_4, SDLK_KP_4},
		{KEY_KP_5, SDLK_KP_5},
		{KEY_KP_6, SDLK_KP_6},
		{KEY_KP_7, SDLK_KP_7},
		{KEY_KP_8, SDLK_KP_8},
		{KEY_KP_9, SDLK_KP_9},
		{KEY_KP_DIVIDE, SDLK_KP_DIVIDE},
		{KEY_KP_MULTIPLY, SDLK_KP_MULTIPLY},
		{KEY_KP_MINUS, SDLK_KP_MINUS},
		{KEY_KP_PLUS, SDLK_KP_PLUS},
		{KEY_KP_ENTER, SDLK_KP_ENTER},
		{KEY_KP_PERIOD, SDLK_KP_PERIOD},

		// Miscellaneous keys
		{KEY_PRINTSCREEN, SDLK_PRINTSCREEN},
		{KEY_SCROLLLOCK, SDLK_SCROLLLOCK},
		{KEY_PAUSE, SDLK_PAUSE}};
};
