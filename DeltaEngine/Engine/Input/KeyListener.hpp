#pragma once
#include <iostream>
#include <set>
#include "DeltaInputs.hpp"

struct KeyListener
{
	std::set<Key> keys;
	bool isPressed;
	int mouseX;
	int mouseY;

	KeyListener(std::set<Key> keys, bool isPressed, int posX, int posY)
	 : keys(keys), isPressed(isPressed), mouseX(posX), mouseY(posY)
	{
	}

	KeyListener() : keys({}), isPressed(false), mouseX(-1), mouseY(-1)
	{
	}
};
