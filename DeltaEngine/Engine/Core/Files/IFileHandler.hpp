#pragma once

#include <string>

#include "json/json.hpp"

using json = nlohmann::json;

class IFileHandler
{
   public:
	virtual ~IFileHandler() = default;

	// Json file management
	virtual json LoadFile(const std::string& path) = 0;
	virtual void SaveFile(const std::string& path, const json& data) = 0;
};
