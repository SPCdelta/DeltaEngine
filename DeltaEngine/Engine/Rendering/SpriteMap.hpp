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
	SpriteMap(const std::string& spritePath, std::vector<SpriteMapEntry> sprites, const std::string& category = "");

	SpriteData* Get(const std::string& spriteName);
};