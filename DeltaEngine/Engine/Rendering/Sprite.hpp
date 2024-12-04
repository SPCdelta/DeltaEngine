#pragma once

#include "Renderables/SpriteRenderable.h"

class Sprite : public SpriteRenderable
{
public:
	Sprite(const std::string& spriteName) : SpriteRenderable(spriteName)
	{ }

	Sprite(const std::string& spriteName, std::shared_ptr<AnimationSheet> sheet) : SpriteRenderable(spriteName, sheet)
	{ }

	void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Camera* camera, const Transform& transform);
};