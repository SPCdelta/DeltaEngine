#pragma once
#include <iostream>
class KeyListener
{
public:
	KeyListener(std::string key, bool isPressed)
		: key(key), isPressed(isPressed)
	{
	}

	const std::string key;
	bool isPressed;
};
