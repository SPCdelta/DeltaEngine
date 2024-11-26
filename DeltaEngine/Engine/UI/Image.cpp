#include "Image.hpp"

using namespace Ui;

void Image::Render(Rendering::Renderer* renderer,
				   const ViewportData& viewportData, const Transform& transform)
{
	// Get Texture
	if (!_texture)
	{
		Rendering::Texture* texture = Rendering::LoadTexture(renderer, sprite);
		if (!texture)
		{
			std::cerr << "Failed to load texture: " << Rendering::GetError()
					  << std::endl;
			return;
		}
		_texture = texture;
	}

	Rendering::Rect destRect;
	destRect.x = static_cast<int>(transform.position.GetX());
	destRect.y = static_cast<int>(transform.position.GetY());

	destRect.w = static_cast<int>(transform.scale.GetX());
	destRect.h = static_cast<int>(transform.scale.GetY());

	Rendering::RenderCopyEx(renderer, _texture, NULL, &destRect, transform.rotation, 0, Rendering::GetFlip(flipX, flipY));
}