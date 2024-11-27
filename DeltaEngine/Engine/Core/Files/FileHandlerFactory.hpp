#pragma once

#include <memory>
#include <string>

#include "IFileHandler.hpp"
#include "JSONFileHandler.hpp"

class FileHandlerFactory
{
	public:
		static std::shared_ptr<IFileHandler> CreateHandler(const std::string& extension)
		{
			if (extension == "json")
			{
				return std::make_shared<JSONFileHandler>();
			}
			// Add more extensions here (e.g., for XML, YAML)
			// else if (extension == "xml") return std::make_shared<XMLFileHandler>();

			throw std::invalid_argument("Unsupported file extension: " + extension);
		}
};