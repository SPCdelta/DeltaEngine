#include "StringUtils.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

const std::string StringUtils::FloatToString(float value, int precision)
{
    std::ostringstream oss;

    oss << std::fixed << std::setprecision(precision) << value;

    return oss.str();
}