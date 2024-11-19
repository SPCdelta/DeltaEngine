#pragma once
#include <iostream>
#include <vector>
#include "InputsEnum.hpp"

struct KeyListener
{
	std::vector<Key> keys;
	bool isPressed;
	int mouseX;
	int mouseY;

	KeyListener(std::vector<Key> keys, bool isPressed, int posX, int posY)
	 : keys(keys), isPressed(isPressed), mouseX(posX), mouseY(posY)
	{
	}

	KeyListener() : keys({}), isPressed(false), mouseX(-1), mouseY(-1)
	{
	}
};
