#pragma once

#include "TextureManager.hpp"

class SpriteMap;

class ResourceManager
{
public:
	static ResourceManager& get_instance() { return instance; }
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	friend class SpriteMap;

	static void Add(const std::string& name, const std::string& spritePath)
	{
		Rendering::Texture* texture = TextureManager::Add(spritePath);
		int width = 0;
		int height = 0;
		Rendering::QueryTexture(texture, nullptr, nullptr, &width, &height);

		SpriteData* spriteData = new SpriteData
		(
			texture,
			{ 0.0f, 0.0f },
			{ static_cast<float>(width), static_cast<float>(height) }
		);
		Add(name, spriteData);
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

	static void Add(const std::string& name, SpriteData* spriteData)
	{
		instance._sprites.emplace(name, spriteData);
	}
};