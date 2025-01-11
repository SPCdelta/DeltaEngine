#include "StringUtils.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

const std::string StringUtils::FloatToString(float value, int precision)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

std::vector<std::string> StringUtils::Split(const std::string& str, char splitValue)
{
	std::vector<std::string> parts;
	size_t pos = 0;
	size_t found;

	while ((found = str.find('_', pos)) != std::string::npos) 
	{
		parts.push_back(str.substr(pos, found - pos));
		pos = found + 1;
	}
	parts.push_back(str.substr(pos));

	return parts;
}

const std::string StringUtils::ToLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
	return result;
}