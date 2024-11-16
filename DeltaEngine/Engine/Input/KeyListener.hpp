#pragma once
#include <iostream>

struct KeyListener
{
	const std::string key;
	bool isPressed;
	int mouseX;
	int mouseY;

	KeyListener(std::string key, bool isPressed, int posX, int posY)
	 : key(key), isPressed(isPressed), mouseX(posX), mouseY(posY)
	{
	}
};
