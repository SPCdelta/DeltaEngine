#pragma once

#include <memory>
#include <string>

#include "IFileHandler.hpp"
#include "JSONFileHandler.hpp"

class FileHandlerFactory
{
public:
	static std::shared_ptr<IFileHandler> CreateHandler(const std::string& extension);
};