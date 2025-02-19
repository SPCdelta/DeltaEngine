#include "Sprite.hpp"

Sprite::Sprite(const std::string& spriteName) 
	: SpriteRenderable(spriteName) 
{

}

Sprite::Sprite(const std::string& spriteName, std::shared_ptr<AnimationSheet> sheet) 
	: SpriteRenderable(spriteName, sheet)
{ 

}

void Sprite::Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Camera* camera, const Transform& transform)
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

	Rendering::ModifyColor(_spriteData->texture, color);

	Rendering::Rect destRect;
	destRect.x = static_cast<int>((transform.position.GetX() - camera->transform.position.GetX()) * viewportData.unitPixelSize) + 
		static_cast<int>(static_cast<float>(viewportData.width) / 2.0f);
	destRect.y = static_cast<int>(viewportData.height - ((transform.position.GetY() - camera->transform.position.GetY()) *
		viewportData.unitPixelSize) - (viewportData.unitPixelSize * transform.scale.GetY())) - 
		static_cast<int>(static_cast<float>(viewportData.height) / 2.0f);

	destRect.w = static_cast<int>(viewportData.unitPixelSize * transform.scale.GetX());
	destRect.h = static_cast<int>(viewportData.unitPixelSize * transform.scale.GetY());
	
	RenderBorder(renderer, destRect);

	if (_sheet)
	{
		Rendering::Rect srcRect = _sheet->GetSrcRect();
		Rendering::RenderCopyEx
		(
			renderer, _spriteData->texture, &srcRect, &destRect, transform.rotation, 0,
			Rendering::GetFlip
			((
				(_sheet->GetFacingDirection() == Direction::RIGHT && _sheet->GetRowRight() == 0) ||
				(_sheet->GetFacingDirection() == Direction::LEFT && _sheet->GetRowLeft() == 0) ||
				(flipX)), flipY
			)
		);
	}
	else
	{
		Rendering::Rect srcRect;
		srcRect.x = static_cast<int>(_spriteData->spriteStart.GetX());
		srcRect.y = static_cast<int>(_spriteData->spriteStart.GetY());
		srcRect.w = static_cast<int>(_spriteData->spriteEnd.GetX() - _spriteData->spriteStart.GetX());
		srcRect.h = static_cast<int>(_spriteData->spriteEnd.GetY() - _spriteData->spriteStart.GetY());

		Rendering::RenderCopyEx(renderer, _spriteData->texture, &srcRect, &destRect, transform.rotation, 0, Rendering::GetFlip(flipX, flipY));
	}
}
