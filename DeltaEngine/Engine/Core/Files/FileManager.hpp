#pragma once

#include <memory>
#include <filesystem>
#include <string>

#include "FileHandlerFactory.hpp"
#include "IFileHandler.hpp"

namespace fs = std::filesystem;

class FileManager
{
	public:
		FileManager() = default;

		Json::json Load(const std::string& path, const std::string& extension)
		{
			auto handler = FileHandlerFactory::CreateHandler(extension);
			return handler->LoadFile(path);
		}

		void Save(const std::string& path, const std::string& extension, const Json::json& data)
		{
			auto handler = FileHandlerFactory::CreateHandler(extension);
			handler->SaveFile(path, data);
		}

		static std::vector<std::string> filesInDirectory(const std::string& directoryPath)
		{
			if (!fs::exists(directoryPath)) {
				if (!fs::create_directory(directoryPath)) {
					std::cerr << "error with making: " + directoryPath + "\n";
				}
			}
			std::vector<std::string> result;
			try {
				for (const auto& entry : fs::directory_iterator(directoryPath)) {
					if (fs::is_regular_file(entry.status())) {
						result.push_back(entry.path().filename().string());
					}
				}
			} catch (const fs::filesystem_error& e) { 
				std::cerr << "Error: " << e.what() << std::endl;
			}
			return result;
		}
};
