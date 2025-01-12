#pragma once

#include "../../../Rendering/Sprite.hpp"
#include "../Json.hpp"

struct SpriteDTO
{
	std::string spriteName;
	Layer layer;

	SpriteDTO ToTransform() const
	{
		return SpriteDTO{ spriteName, layer };
	}

	static void ToJson(Json::json& tileJson, Sprite  sprite) 
	{
		tileJson["sprite"]["name"] = sprite.GetSprite();
		tileJson["sprite"]["layer"] = sprite.GetLayer();
	}

	static SpriteDTO  JsonToSpriteData(Json::json& tile) 
	{
		return
		{
			tile["sprite"]["name"],
			static_cast<Layer>(tile["sprite"]["layer"])
		};
	}
};
