#include "Image.hpp"

using namespace Ui;

Image::Image(const std::string& spriteName) 
	: SpriteRenderable(spriteName) 
{

}

void Image::Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Transform& transform)
{
	// Get Texture
	if (!_spriteData)
	{
		if (_spriteName.empty())
			throw std::exception("Sprite not set on Sprite Component");

		_spriteData = ResourceManager::Get(_spriteName);
		if (!_spriteData)
			throw std::exception("Sprite not found");
	}

	Rendering::Rect srcRect;
	srcRect.x = static_cast<int>(_spriteData->spriteStart.GetX());
	srcRect.y = static_cast<int>(_spriteData->spriteStart.GetY());
	srcRect.w = static_cast<int>(_spriteData->spriteEnd.GetX() - srcRect.x);
	srcRect.h = static_cast<int>(_spriteData->spriteEnd.GetY() - srcRect.y);

	Rendering::Rect destRect;
	destRect.x = static_cast<int>(transform.position.GetX());
	destRect.y = static_cast<int>(transform.position.GetY());
	destRect.w = static_cast<int>(transform.scale.GetX());
	destRect.h = static_cast<int>(transform.scale.GetY());

	Rendering::ModifyColor(_spriteData->texture, color);
	Rendering::RenderCopyEx(renderer, _spriteData->texture, &srcRect, &destRect, transform.rotation, 0, Rendering::GetFlip(flipX, flipY));
}