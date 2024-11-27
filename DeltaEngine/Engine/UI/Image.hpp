#pragma once

#include "../Rendering/Renderable.hpp"

namespace Ui
{
	class Image : public Renderable
	{
	public:
		Image(const char* spritePath) : Renderable(spritePath) {}
		void Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Transform& transform);
	};
}
