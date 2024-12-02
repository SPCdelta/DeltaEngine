#pragma once

#include <string>
#include <vector>

#include "../Core/Math/Vector2.hpp"
#include "SpriteData.hpp"
#include "Managers.hpp"

struct TilemapEntry	 // DTO
{
	std::string spriteName;
	std::string spritePath;
	Math::Vector2 spriteStart;
	Math::Vector2 spriteEnd;
};

class SpriteMap
	{
	public:
		SpriteMap(const std::string& name, std::vector<TilemapEntry> sprites)
			: _name{ name }
		{
			// Convert TilemapEntry DTO into SpriteData
			for (TilemapEntry& entry : sprites)
			{
				TextureManager::Add(entry.spritePath);

				SpriteData* spriteData = new SpriteData
				(
					TextureManager::Get(entry.spritePath),
					entry.spriteStart,
					entry.spriteEnd
				);
				ResourceManager::Add(entry.spriteName, spriteData);
			}
		}

		SpriteData* Get(const std::string& spriteName)
		{
			return ResourceManager::Get(spriteName);
		}

	private:
		std::string _name;
	};