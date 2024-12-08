#pragma once

#include "TextureManager.hpp"
#include "../UI/FontManager.hpp"
#include <unordered_map>
#include <algorithm>

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
	static void AddFont(const std::string& fontName, const std::string& fontPath)
	{
		FontManager::AddFont(fontName, fontPath);
	}

	static Font::Font* GetFont(const std::string& name, int fontSize)
	{
		return FontManager::Get(name, fontSize);
	}

	// Sprites
	static void AddSprite(const std::string& name, const std::string& spritePath, const std::string& category = "")
	{
		Rendering::Texture* texture = TextureManager::Add(spritePath);
		int width = 0;
		int height = 0;
		Rendering::QueryTexture(texture, nullptr, nullptr, &width, &height);
		std::string category_ = category.empty() ? name : category;

		SpriteData* spriteData = new SpriteData
		(
			texture,
			{ 0.0f, 0.0f },
			{ static_cast<float>(width), static_cast<float>(height) },
			category_
		);
		AddSprite(name, spriteData);
	}

	static SpriteData* Get(const std::string& name)
	{
		if (!instance._sprites.contains(name))
			throw new std::exception("Sprite das not exist!!");
		return instance._sprites[name];
	}

	static std::unordered_map<std::string, SpriteData*>& GetAllSprites() {
		return instance._sprites;
	}

	static std::unordered_map<std::string, SpriteData*> GetSprites(std::vector<std::string> categories){
		std::unordered_map<std::string, SpriteData*> result;
		for (const auto& pair : instance._sprites) {
			if (pair.second && std::find(categories.begin(), categories.end(), pair.second->category) != categories.end() ) {
				result[pair.first] = pair.second;
			}
		}
		return result;
	}


	static void Cleanup() 
	{
		TextureManager::Cleanup();
		FontManager::Cleanup();
	}

private:
	static ResourceManager instance;
	std::unordered_map<std::string, SpriteData*> _sprites;
	std::unordered_map<std::string, Font::Font*> _fonts;

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