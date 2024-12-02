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

	static void Add(const std::string& spritePath) 
	{ 
		if (instance._textures.find(spritePath) == instance._textures.end())
		{
			Rendering::Texture* texture = Rendering::LoadTexture(instance._renderer, spritePath.c_str());
			instance._textures.emplace(spritePath, texture);
		}
	}

	static Rendering::Texture* Get(const std::string& spritePath)
	{ 
		return instance._textures[spritePath];
	}

private:
	static TextureManager instance;
	SDL_Renderer* _renderer = nullptr;
	std::map<std::string, Rendering::Texture*> _textures;

	TextureManager() { };
	~TextureManager() 
	{
		// Delete all entries in map
		for (const auto& pair : _textures)
		{
			delete pair.second;
		}
	}
};

class ResourceManager
{
public:
	static ResourceManager& get_instance() { return instance; }
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	static void Add(const std::string& name, SpriteData* spriteData)
	{
		instance._sprites.emplace(name, spriteData);
	}

	static SpriteData* Get(const std::string& name)
	{
		return instance._sprites[name];
	}

private:
	static ResourceManager instance;
	std::map<std::string, SpriteData*> _sprites;

	ResourceManager() { }
	~ResourceManager()
	{
		// Delete all entries in map
		for (const auto& pair : _sprites)
		{
			delete pair.second;
		}
	}
};