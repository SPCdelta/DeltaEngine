#pragma once

#include <memory>
#include <string>

#include "FileHandlerFactory.hpp"
#include "IFileHandler.hpp"

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
};
