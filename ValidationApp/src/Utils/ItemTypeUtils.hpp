#pragma once

#include <string>

class ItemTypeUtils
{
public:
	static const std::string GetHeader(const std::string& type);
	static const std::string GetBody(const std::string& type);
};

