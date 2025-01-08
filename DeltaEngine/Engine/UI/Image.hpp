#pragma once

#include "../Rendering/Renderables/SpriteRenderable.hpp"

namespace Ui
{
	class Image : public SpriteRenderable
	{
	public:
		Image(const std::string& spriteName);

		void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Transform& transform);
	};
}
