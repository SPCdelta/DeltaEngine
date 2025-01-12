#include "SpriteMap.hpp"

SpriteMap::SpriteMap(const std::string& spritePath, std::vector<SpriteMapEntry> sprites, const std::string& category)
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

SpriteData* SpriteMap::Get(const std::string& spriteName)
{
	return ResourceManager::Get(spriteName);
}