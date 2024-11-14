#include "Sprite.hpp"

Sprite::Sprite(const char* spritePath) : sprite(spritePath)
{
	// TODO
	
}

Sprite::~Sprite()
{
	// TODO
}

void Sprite::Render(Rendering::Renderer* renderer, Math::Vector2 position, Math::Vector2 scale)
{
	// TODO

	Rendering::Texture* texture = Rendering::LoadTexture(renderer, sprite);
	if (!texture)
	{
		std::cerr << "Failed to load texture: " << Rendering::GetError() << std::endl;
		return; // TODO, throw?
	}

	_texture = texture;

	Rendering::Rect srcRect = {position.GetX(), position.GetY(), scale.GetX(), scale.GetY()};
	Rendering::Rect destRect = {position.GetX(), position.GetY(), scale.GetX(), scale.GetY()}; // TODO diff pos?

	/*Rendering::Rect* srcRect = {sprite.getPosX(), sprite.getPosY(), size, size};
	Rendering::Rect* destRect = {gridPosX * (size * tileScaler),
						 gridPosY * (size * tileScaler), size * tileScaler,
						 size * tileScaler};*/

	Rendering::RendererFlip flip = flipX ? Rendering::FLIP_HORIZONTAL : Rendering::FLIP_NONE;
	/*Rendering::RendererFlip flip = flipY ? Rendering::FLIP_VERTICAL : Rendering::FLIP_NONE;*/ // TODO ?
	Rendering::RenderCopyEx(renderer, _texture, &srcRect, &destRect, 0, NULL, flip);
	Rendering::RenderPresent(renderer);
}

void Sprite::StopRendering()
{
	Rendering::DestroyTexture(_texture);
}

void Sprite::FlipHorizontally() 
{
	flipX = !flipX;
}

void Sprite::FlipVertically() 
{
	flipY = !flipY;
}
