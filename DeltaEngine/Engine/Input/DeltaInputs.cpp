#include "DeltaInputs.hpp"


const std::unordered_map<Key, std::string> InputsEnum::keyMap = {
	{KEY_A, "A"},
	{KEY_B, "B"},
	{KEY_C, "C"},
	{KEY_D, "D"},
	{KEY_E, "E"},
	{KEY_F, "F"},
	{KEY_G, "G"},
	{KEY_H, "H"},
	{KEY_I, "I"},
	{KEY_J, "J"},
	{KEY_K, "K"},
	{KEY_L, "L"},
	{KEY_M, "M"},
	{KEY_N, "N"},
	{KEY_O, "O"},
	{KEY_P, "P"},
	{KEY_Q, "Q"},
	{KEY_R, "R"},
	{KEY_S, "S"},
	{KEY_T, "T"},
	{KEY_U, "U"},
	{KEY_V, "V"},
	{KEY_W, "W"},
	{KEY_X, "X"},
	{KEY_Y, "Y"},
	{KEY_Z, "Z"},

	// Numbers
	{KEY_0, "0"},
	{KEY_1, "1"},
	{KEY_2, "2"},
	{KEY_3, "3"},
	{KEY_4, "4"},
	{KEY_5, "5"},
	{KEY_6, "6"},
	{KEY_7, "7"},
	{KEY_8, "8"},
	{KEY_9, "9"},

	// Function keys
	{KEY_F1, "F1"},
	{KEY_F2, "F2"},
	{KEY_F3, "F3"},
	{KEY_F4, "F4"},
	{KEY_F5, "F5"},
	{KEY_F6, "F6"},
	{KEY_F7, "F7"},
	{KEY_F8, "F8"},
	{KEY_F9, "F9"},
	{KEY_F10, "F10"},
	{KEY_F11, "F11"},
	{KEY_F12, "F12"},

	// Arrows
	{KEY_UP, "UP"},
	{KEY_DOWN, "DOWN"},
	{KEY_LEFT, "LEFT"},
	{KEY_RIGHT, "RIGHT"},

	// Modifiers
	{KEY_LSHIFT, "LSHIFT"},
	{KEY_RSHIFT, "RSHIFT"},
	{KEY_LCTRL, "LCTRL"},
	{KEY_RCTRL, "RCTRL"},
	{KEY_LALT, "LALT"},
	{KEY_RALT, "RALT"},

	// Special keys
	{KEY_TAB, "TAB"},
	{KEY_CAPSLOCK, "CAPSLOCK"},
	{KEY_BACKSPACE, "BACKSPACE"},
	{KEY_ENTER, "ENTER"},
	{KEY_ESCAPE, "ESCAPE"},
	{KEY_SPACE, "SPACE"},
	{KEY_DELETE, "DELETE"},
	{KEY_HOME, "HOME"},
	{KEY_END, "END"},
	{KEY_PAGEUP, "PAGEUP"},
	{KEY_PAGEDOWN, "PAGEDOWN"},
	{KEY_INSERT, "INSERT"},

	// Symbols
	{KEY_COMMA, ","},
	{KEY_PERIOD, "."},
	{KEY_SLASH, "/"},
	{KEY_SEMICOLON, ";"},
	{KEY_APOSTROPHE, "'"},
	{KEY_LEFTBRACKET, "["},
	{KEY_RIGHTBRACKET, "]"},
	{KEY_BACKSLASH, "\\"},
	{KEY_MINUS, "-"},
	{KEY_EQUALS, "="},
	{KEY_GRAVE, "`"},

	// Keypad
	{KEY_KP_0, "KP_0"},
	{KEY_KP_1, "KP_1"},
	{KEY_KP_2, "KP_2"},
	{KEY_KP_3, "KP_3"},
	{KEY_KP_4, "KP_4"},
	{KEY_KP_5, "KP_5"},
	{KEY_KP_6, "KP_6"},
	{KEY_KP_7, "KP_7"},
	{KEY_KP_8, "KP_8"},
	{KEY_KP_9, "KP_9"},
	{KEY_KP_DIVIDE, "KP_DIVIDE"},
	{KEY_KP_MULTIPLY, "KP_MULTIPLY"},
	{KEY_KP_MINUS, "KP_MINUS"},
	{KEY_KP_PLUS, "KP_PLUS"},
	{KEY_KP_ENTER, "KP_ENTER"},
	{KEY_KP_PERIOD, "KP_PERIOD"},

	// Miscellaneous
	{KEY_PRINTSCREEN, "PRINTSCREEN"},
	{KEY_SCROLLLOCK, "SCROLLLOCK"},
	{KEY_PAUSE, "PAUSE"},
	{KEY_UNKNOWN, "UNKNOWN"}};

const std::vector<MouseButton> InputsEnum::buttonVector = {
	MouseButton::Left,	  
	MouseButton::Middle,
	MouseButton::Right, 
	MouseButton::Button4, 
	MouseButton::Button5, 
	MouseButton::Unknown};


const std::unordered_map<Key, std::string>& InputsEnum::getKeyMap()
{
	return keyMap;
}

const Key InputsEnum::toKey(const std::string& key)
{
	for (const auto& pair : keyMap)
	{
		if (pair.second == key)
		{
			return pair.first;
		}
	}
	return KEY_UNKNOWN;
}

const std::string& InputsEnum::toStr(Key key)
{
	auto it = keyMap.find(key);
	if (it != keyMap.end())
	{
		return it->second;
	}
	return keyMap.at(KEY_UNKNOWN);
}

const std::vector<MouseButton>& InputsEnum::getButtonVector()
{
	return buttonVector;
}

const MouseButton InputsEnum::toButton(int button)
{
	if (button < 1 || button > buttonVector.size())
		return MouseButton::Unknown;

	return buttonVector[button - 1];
}

const int InputsEnum::toInt(MouseButton button)
{
	return static_cast<int>(button);
}
