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
		SpriteMap(const std::string& spritePath, std::vector<SpriteMapEntry> sprites, const std::string& category = "")
		{
			// Convert SpritemapEntry DTO into SpriteData
			
			std::string spriteCategory = category;
			for (SpriteMapEntry& entry : sprites)
			{
				TextureManager::Add(spritePath);

				if (category.empty())
					spriteCategory = entry.spriteName;

				SpriteData* spriteData = new SpriteData
				(
					TextureManager::Get(spritePath),
					entry.spriteStart,
					entry.spriteEnd,
					spriteCategory
				);
				ResourceManager::AddSprite(entry.spriteName, spriteData);
			}
		}

		SpriteData* Get(const std::string& spriteName)
		{
			return ResourceManager::Get(spriteName);
		}

	};