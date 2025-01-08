#include "ResourceManager.hpp"

ResourceManager ResourceManager::instance;

ResourceManager::ResourceManager() 
{

}

ResourceManager::~ResourceManager()
{
	// Delete all entries in map
	for (const auto& pairsprite : _sprites)
	{
		delete pairsprite.second;
	}
}