#pragma once

#include <fstream>
#include <iostream>

#include "Json.hpp"
#include "IFileHandler.hpp"

class JSONFileHandler : public IFileHandler
{
public:
	static const int TAB_SPACE = 4;

	// 'Assets\\Files\\' needs to be in the path with the file name at the end
	Json::json LoadFile(const std::string& path) override;

	// 'Assets\\Files\\' needs to be in the path with the file name at the end
	void SaveFile(const std::string& path, const Json::json& data) override;
};