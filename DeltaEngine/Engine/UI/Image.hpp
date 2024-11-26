#pragma once

#include "../Rendering/Renderable.hpp"

class Image : public Renderable
{
public:
	Image(const char* spritePath) : Renderable(spritePath) {}

	Image(const char* spritePath, std::shared_ptr<SpriteSheet> sheet)
		: Renderable(spritePath, sheet)
	{ }

	void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Transform& transform);
};