#pragma once

#include <string>
#include <vector>

class StringUtils
{
public:
	static const std::string FloatToString(float value, int precision);
	static std::vector<std::string> Split(const std::string& str, char splitValue);
	static const std::string ToLower(const std::string& str);
};

