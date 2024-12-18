#pragma once

#include <iostream>
#include <string>

class MySceneData
{
public:
	MySceneData(int a, int b, const std::string& text) 
		: _a{a}, _b{ b }, _text{ text }
	{

	}

	void Print() const
	{
		std::cout << _text << ": " << _a << " : " << _b << std::endl;
	}

	int _a;
	int _b;
	std::string _text;
};