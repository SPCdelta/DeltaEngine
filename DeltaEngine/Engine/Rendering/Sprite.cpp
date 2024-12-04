#include "Sprite.hpp"

void Sprite::Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Camera* camera, const Transform& transform)
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

	Rendering::ModifyColor(_spriteData->texture, color);

	Rendering::Rect destRect;
	destRect.x = static_cast<int>(
		(transform.position.GetX() - camera->transform.position.GetX()) *
		viewportData.unitPixelSize);
	destRect.y = static_cast<int>(
		viewportData.height -
		((transform.position.GetY() - camera->transform.position.GetY()) *
		 viewportData.unitPixelSize) -
		(transform.scale.GetY() * viewportData.unitPixelSize));

	destRect.w =
		(static_cast<int>(transform.scale.GetX()) * viewportData.unitPixelSize);
	destRect.h =
		(static_cast<int>(transform.scale.GetY()) * viewportData.unitPixelSize);

	if (_sheet)
	{
		Rendering::Rect srcRect = _sheet->GetSrcRect();
		Rendering::RenderCopyEx(
			renderer, _spriteData->texture, &srcRect, &destRect, transform.rotation, 0,
			Rendering::GetFlip(
				((_sheet->GetFacingDirection() == Direction::RIGHT &&
				  _sheet->GetRowRight() == 0) ||
				 (_sheet->GetFacingDirection() == Direction::LEFT &&
				  _sheet->GetRowLeft() == 0) ||
				 (flipX)),
				flipY));
	}
	else
	{
		Rendering::Rect srcRect;
		srcRect.x = _spriteData->spriteStart.GetX();
		srcRect.y = _spriteData->spriteStart.GetY();
		srcRect.w = _spriteData->spriteEnd.GetX() - _spriteData->spriteStart.GetX();
		srcRect.h = _spriteData->spriteEnd.GetY() - _spriteData->spriteStart.GetY();

		Rendering::RenderCopyEx(renderer, _spriteData->texture, &srcRect, &destRect,
								transform.rotation, 0,
								Rendering::GetFlip(flipX, flipY));
	}
}
