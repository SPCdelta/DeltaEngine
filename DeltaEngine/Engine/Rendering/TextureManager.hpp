#pragma once

#include <map>
#include <string>

#include "SpriteData.hpp"

class TextureManager
{
   public:
	static TextureManager& get_instance() { return instance; }
	TextureManager(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	static void SetRenderer(SDL_Renderer* renderer)
	{
		instance._renderer = renderer;
	}

	static Rendering::Texture* Add(const std::string& spritePath)
	{
		if (instance._textures.find(spritePath) == instance._textures.end())
		{
			Rendering::Texture* texture =
				Rendering::LoadTexture(instance._renderer, spritePath.c_str());
			instance._textures.emplace(spritePath, texture);
			return texture;
		}

		return nullptr;
	}

	static Rendering::Texture* Get(const std::string& spritePath)
	{
		return instance._textures[spritePath];
	}

	static void Cleanup()
	{
		// Delete all entries in map
		for (const auto& pair : instance._textures)
		{
			// no leaks? okidokie!
			Rendering::DestroyTexture(pair.second);
		}
	}

   private:
	static TextureManager instance;
	SDL_Renderer* _renderer = nullptr;
	std::map<std::string, Rendering::Texture*> _textures;

	TextureManager(){};
};