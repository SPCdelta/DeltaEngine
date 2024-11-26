#include "Image.hpp"

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

	// TODO: Facade
	SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);

	Rendering::Rect destRect;
	destRect.x = static_cast<int>(transform.position.GetX());
	destRect.y = static_cast<int>(transform.position.GetY());

	destRect.w = static_cast<int>(transform.scale.GetX());
	destRect.h = static_cast<int>(transform.scale.GetY());

	if (_sheet)
	{
		Rendering::Rect srcRect = _sheet->GetSrcRect();
		Rendering::RenderCopyEx(
			renderer, _texture, &srcRect, &destRect, transform.rotation, 0,
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
		Rendering::RenderCopyEx(renderer, _texture, NULL, &destRect, transform.rotation, 0, Rendering::GetFlip(flipX, flipY));
	}
}