#pragma once

#include "TextureManager.hpp"
#include "../UI/FontManager.hpp"

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

	// Fonts
	//static void AddFont(const std::string& name, const std::string& fontPath)
	//{
	//	instance._fonts.emplace(name, Font::OpenFont(fontPath, 16));
	//}

	//static Font::Font* GetFont(const std::string& name)
	//{
	//	return instance._fonts[name];
	//}
	static void AddFont(const std::string& fontName, const std::string& fontPath)
	{
		FontManager::AddFont(fontName, fontPath);
	}

	static Font::Font* GetFont(const std::string& name, int fontSize)
	{
		return FontManager::Get(name, fontSize);
	}

	// Sprites
	static void AddSprite(const std::string& name, const std::string& spritePath)
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
		AddSprite(name, spriteData);
	}

	static SpriteData* Get(const std::string& name)
	{
		return instance._sprites[name];
	}

	static std::map<std::string, SpriteData*>& GetAllSprites() {
		return instance._sprites;
	}

	static void Cleanup() 
	{
		TextureManager::Cleanup();
		FontManager::Cleanup();
	}

private:
	static ResourceManager instance;
	std::map<std::string, SpriteData*> _sprites;
	std::map<std::string, Font::Font*> _fonts;

	ResourceManager() { }
	~ResourceManager()
	{
		// Delete all entries in map
		for (const auto& pairsprite : _sprites)
		{
			delete pairsprite.second;
		}


	}

	static void AddSprite(const std::string& name, SpriteData* spriteData)
	{
		instance._sprites.emplace(name, spriteData);
	}
};