#pragma once
#include <iostream>
#include <vector>

struct KeyListener
{
	std::vector<std::string> keys;
	bool isPressed;
	int mouseX;
	int mouseY;

	KeyListener(std::vector<std::string> keys, bool isPressed, int posX, int posY)
	 : keys(keys), isPressed(isPressed), mouseX(posX), mouseY(posY)
	{
	}

	KeyListener() : keys({}), isPressed(false), mouseX(-1), mouseY(-1)
	{
	}
};
