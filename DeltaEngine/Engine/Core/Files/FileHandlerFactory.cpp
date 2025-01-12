#include "FileHandlerFactory.hpp"

std::shared_ptr<IFileHandler> FileHandlerFactory::CreateHandler(const std::string& extension)
{
	if (extension == "json")
		return std::make_shared<JSONFileHandler>();
	// Add more extensions here (e.g., for XML, YAML)

	throw std::invalid_argument("Unsupported file extension: " + extension);
}