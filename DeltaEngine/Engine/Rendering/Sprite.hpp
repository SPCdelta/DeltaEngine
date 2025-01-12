#pragma once

#include "Renderables/SpriteRenderable.hpp"

class Sprite : public SpriteRenderable
{
public:
	Sprite(const std::string& spriteName);
	Sprite(const std::string& spriteName, std::shared_ptr<AnimationSheet> sheet);

	void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Camera* camera, const Transform& transform);
};