#include "Image.hpp"

using namespace Ui;

void Image::Render(Rendering::Renderer* renderer,
				   const ViewportData& viewportData, const Transform& transform)
{
	// Get Texture
	if (!_spriteData)
	{
		if (_spriteName)
		{
			throw std::exception("Sprite not set on Sprite Component");
		}

		_spriteData = ResourceManager::Get(_spriteName);
		if (!_spriteData)
		{
			throw std::exception("Sprite not found");
		}
	}

	Rendering::Rect srcRect;
	srcRect.x = _spriteData->spriteStart.GetX();
	srcRect.y = _spriteData->spriteStart.GetY();
	srcRect.w = _spriteData->spriteEnd.GetX() - _spriteData->spriteStart.GetX();
	srcRect.h = _spriteData->spriteEnd.GetY() - _spriteData->spriteStart.GetY();

	Rendering::Rect destRect;
	destRect.x = static_cast<int>(transform.position.GetX());
	destRect.y = static_cast<int>(transform.position.GetY());

	destRect.w = static_cast<int>(transform.scale.GetX());
	destRect.h = static_cast<int>(transform.scale.GetY());

	Rendering::RenderCopyEx(renderer, _spriteData->texture, &srcRect, &destRect, transform.rotation, 0, Rendering::GetFlip(flipX, flipY));
}