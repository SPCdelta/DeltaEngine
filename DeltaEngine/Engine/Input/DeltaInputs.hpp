#pragma once
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>

enum Key
{
	// Alphabet keys
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,

	// Number keys
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,

	// Function keys
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,

	// Arrow keys
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,

	// Modifier keys
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LCTRL,
	KEY_RCTRL,
	KEY_LALT,
	KEY_RALT,

	// Special keys
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_BACKSPACE,
	KEY_ENTER,
	KEY_ESCAPE,
	KEY_SPACE,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_INSERT,

	// Symbol keys
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_LEFTBRACKET,
	KEY_RIGHTBRACKET,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUALS,
	KEY_GRAVE,

	// Keypad (numpad) keys
	KEY_KP_0,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY,
	KEY_KP_MINUS,
	KEY_KP_PLUS,
	KEY_KP_ENTER,
	KEY_KP_PERIOD,

	// Miscellaneous keys
	KEY_PRINTSCREEN,
	KEY_SCROLLLOCK,
	KEY_PAUSE,
	KEY_UNKNOWN
};

enum class MouseButton
{
	Left,		  // Left mouse button
	Middle,		  // Middle mouse button (usually the scroll wheel button)
	Right,		  // Right mouse button
	Button4,	  // Additional button 4 (commonly found on gaming mice)
	Button5,	  // Additional button 5 (commonly found on gaming mice)
	Unknown		  // Any unrecognized button
};

enum InputState
{
	PressedDown,
	Pressed,
	Release,
	Unknown
};

struct Input
{
	std::set<Key> keys;
	std::set<MouseButton> buttons;
	int mouseY;
	int mouseX;
	int wheelVertically;
};

struct MousePosition{
	int mouseY;
	int mouseX;
};


class InputsEnum
{
   public:
	static const std::unordered_map<Key, std::string>& getKeyMap();

	static const std::string& toStr(Key key);

	static const std::vector<MouseButton>& getButtonVector();

	static const MouseButton toButton(int button);
	static const int toInt(MouseButton button);

   private:
	static const std::unordered_map<Key, std::string> keyMap;
	static const std::vector<MouseButton> buttonVector;
};
