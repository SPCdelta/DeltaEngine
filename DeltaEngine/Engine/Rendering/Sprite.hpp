#pragma once

#include "Renderable.hpp"

class Sprite : public Renderable
{
public:
	Sprite(const char* spritePath) : Renderable(spritePath)
	{ }

	Sprite(const char* spritePath, std::shared_ptr<SpriteSheet> sheet) : Renderable(spritePath, sheet)
	{ }

	void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Camera* camera, const Transform& transform);

private:
	Layer _layer{Layer::Default};
};