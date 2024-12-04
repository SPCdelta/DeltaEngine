#pragma once

#include "../Rendering/Renderables/SpriteRenderable.h"

namespace Ui
{
class Image : public SpriteRenderable
	{
	public:
		Image(const std::string& spriteName) : SpriteRenderable(spriteName) {}
		void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Transform& transform);
	};
}
