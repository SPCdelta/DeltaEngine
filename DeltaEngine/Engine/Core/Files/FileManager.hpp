#pragma once

#include <memory>
#include <filesystem>
#include <string>
#include <iostream>

#include "FileHandlerFactory.hpp"
#include "IFileHandler.hpp"

namespace fs = std::filesystem;

class FileManager
{
public:
	FileManager() = default;

	Json::json Load(const std::string& path, const std::string& extension);
	void Save(const std::string& path, const std::string& extension, const Json::json& data);

	static std::vector<std::string> filesInDirectory(const std::string& directoryPath);
	
	static bool FileExists(const std::string& path);
	static void RemoveFile(const std::string& path);
};
