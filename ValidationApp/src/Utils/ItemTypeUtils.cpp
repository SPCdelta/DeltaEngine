#include "ItemTypeUtils.hpp"

const std::string ItemTypeUtils::GetHeader(const std::string& type)
{
    size_t colonPos = type.find(':');

    if (colonPos != std::string::npos)
    {
        return type.substr(0, colonPos);
    }

    return type;
}

const std::string ItemTypeUtils::GetBody(const std::string& type)
{
    size_t colonPos = type.find(':');

    if (colonPos != std::string::npos)
    {
        return type.substr(colonPos + 1);
    }

    return type;
}
