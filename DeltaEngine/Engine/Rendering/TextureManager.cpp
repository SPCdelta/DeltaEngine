#include "TextureManager.hpp"

TextureManager TextureManager::instance;

TextureManager& TextureManager::get_instance()
{
	return instance;
}

TextureManager::TextureManager()
{

}

void TextureManager::SetRenderer(Rendering::Renderer* renderer)
{
	instance._renderer = renderer;
}

Rendering::Texture* TextureManager::Add(const std::string& spritePath)
{
	if (instance._textures.find(spritePath) == instance._textures.end())
	{
		Rendering::Texture* texture = Rendering::LoadTexture(instance._renderer, spritePath.c_str());
		if (texture == nullptr)
			throw new std::exception("Asset das not exist");

		instance._textures.emplace(spritePath, texture);
		return texture;
	}
	return nullptr;
}

Rendering::Texture* TextureManager::Get(const std::string& spritePath)
{
	return instance._textures[spritePath];
}

void TextureManager::Cleanup()
{
	// Delete all entries in map
	for (const auto& pair : instance._textures)
		Rendering::DestroyTexture(pair.second);
}