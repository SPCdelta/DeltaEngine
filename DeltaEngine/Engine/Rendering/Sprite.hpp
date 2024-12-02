#pragma once

#include "Renderable.hpp"

class Sprite : public Renderable
{
public:
	Sprite(const char* spriteName) : Renderable(spriteName)
	{ }

	Sprite(const char* spriteName, std::shared_ptr<SpriteSheet> sheet) : Renderable(spriteName, sheet)
	{ }

	void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Camera* camera, const Transform& transform);
};