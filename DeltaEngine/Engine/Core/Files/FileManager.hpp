#pragma once

#include <memory>
#include <string>

#include "FileHandlerFactory.hpp"
#include "IFileHandler.hpp"

#include "json/json.hpp"

using json = nlohmann::json;

class FileManager
{
	public:
		FileManager() = default;

		json Load(const std::string& path, const std::string& extension)
		{
			auto handler = FileHandlerFactory::CreateHandler(extension);
			return handler->LoadFile(path);
		}

		void Save(const std::string& path, const std::string& extension, const json& data)
		{
			auto handler = FileHandlerFactory::CreateHandler(extension);
			handler->SaveFile(path, data);
		}
};
