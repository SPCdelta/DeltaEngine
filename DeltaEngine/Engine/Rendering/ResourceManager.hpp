#pragma once

#include <cassert>
#include <unordered_map>
#include <algorithm>

#include "TextureManager.hpp"
#include "../UI/FontManager.hpp"
#include "../Audio/AudioManager.hpp"

class SpriteMap;

class ResourceManager
{
public:
	static ResourceManager& get_instance();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	friend class SpriteMap;

	// Fonts
	static void AddFont(const std::string& fontName, const std::string& fontPath);
	static std::shared_ptr<FontWrapper> GetFont(const std::string& name, int fontSize);

	// Sprites
	static void AddSprite(const std::string& name, const std::string& spritePath, const std::string& category = "");
	static SpriteData* Get(const std::string& name);
	static std::unordered_map<std::string, SpriteData*>& GetAllSprites();
	static std::unordered_map<std::string, SpriteData*> GetSprites(std::vector<std::string> categories);

	// Audio
	static void AddAudio(const std::string& name, const std::string& path);
	static const std::string& GetAudio(const std::string& name);

	static void Cleanup();

private:
	static ResourceManager instance;
	std::unordered_map<std::string, SpriteData*> _sprites;
	std::unordered_map<std::string, Font::Font*> _fonts;
	std::unordered_map<std::string, std::string> _audio;

	ResourceManager();
	~ResourceManager();

	static void AddSprite(const std::string& name, SpriteData* spriteData);
};