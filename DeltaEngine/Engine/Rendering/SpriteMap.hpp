#pragma once

#include <string>
#include <vector>

#include "../Core/Math/Vector2.hpp"
#include "SpriteData.hpp"
#include "ResourceManager.hpp"

struct SpriteMapEntry // DTO
{
	std::string spriteName;
	Math::Vector2 spriteStart;
	Math::Vector2 spriteEnd;
};

class SpriteMap
	{
	public:
		SpriteMap(const std::string& category, const std::string& spritePath, std::vector<SpriteMapEntry> sprites)
		{
			// Convert SpritemapEntry DTO into SpriteData
			for (SpriteMapEntry& entry : sprites)
			{
				TextureManager::Add(spritePath);

				SpriteData* spriteData = new SpriteData
				(
					TextureManager::Get(spritePath),
					entry.spriteStart,
					entry.spriteEnd,
					category
				);
				ResourceManager::AddSprite(entry.spriteName, spriteData);
			}
		}

		SpriteData* Get(const std::string& spriteName)
		{
			return ResourceManager::Get(spriteName);
		}

	};