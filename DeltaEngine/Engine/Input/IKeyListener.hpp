#pragma once
#include <iostream>
class IKeyListener
{
public:
	IKeyListener(std::string key) : key(key) {}

	const std::string key;

};
