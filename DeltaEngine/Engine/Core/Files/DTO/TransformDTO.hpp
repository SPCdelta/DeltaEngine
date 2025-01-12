#pragma once

#include "../../../Transform.hpp"
#include "../Json.hpp"

struct TransformDTO
{
	float posX, posY;
	float rotation;
	float scaleX, scaleY;

	Transform ToTransform() const
	{
		return Transform{{posX, posY}, rotation, {scaleX, scaleY}};
	}

	static void ToJson(Json::json& tileJson, Transform transform)
	{
		tileJson["transform"]["position"]["x"] = transform.position.GetX();
		tileJson["transform"]["position"]["y"] = transform.position.GetY();
		tileJson["transform"]["rotation"] = transform.rotation;
		tileJson["transform"]["scale"]["x"] = transform.scale.GetX();
		tileJson["transform"]["scale"]["y"] = transform.scale.GetY();
	}

	static Transform JsonToTransform(Json::json& tile)
	{
		return
		{
			{
				static_cast<float>(tile["transform"]["position"]["x"]),
				static_cast<float>(tile["transform"]["position"]["y"])
			},
			static_cast<float>(tile["transform"]["rotation"]),
			{
				static_cast<float>(tile["transform"]["scale"]["x"]),
				static_cast<float>(tile["transform"]["scale"]["y"])
			}
		};
	}
};
