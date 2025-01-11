#pragma once

#include <unordered_map>
#include <string>

#include "SpriteData.hpp"

class TextureManager
{
public:
	static TextureManager& get_instance();

	TextureManager(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	static void SetRenderer(Rendering::Renderer* renderer);

	static Rendering::Texture* Add(const std::string& spritePath);
	static Rendering::Texture* Get(const std::string& spritePath);

	static void Cleanup();

private:
	static TextureManager instance;
	Rendering::Renderer* _renderer = nullptr;
	std::unordered_map<std::string, Rendering::Texture*> _textures;

	TextureManager();
};