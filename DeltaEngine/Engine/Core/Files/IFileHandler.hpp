#pragma once

#include <string>

#include "Json.hpp"

class IFileHandler
{
public:
	virtual ~IFileHandler() = default;

	// Json file management
	virtual Json::json LoadFile(const std::string& path) = 0;
	virtual void SaveFile(const std::string& path, const Json::json& data) = 0;
};
