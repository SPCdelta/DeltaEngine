#include "Sprite.hpp"

Sprite::Sprite(std::string spritePath) : sprite(spritePath)
{
	// TODO
	
}

Sprite::~Sprite()
{
	// TODO
}

void Sprite::Render(Rendering::Renderer* renderer, Math::Vector2 position)
{
	// TODO

	Rendering::Texture* texture = Rendering::LoadTexture(renderer, sprite.c_str());
	if (!texture)
	{
		std::cerr << "Failed to load texture: " << Rendering::GetError() << std::endl;
		return; // TODO, throw?
	}

	_texture = texture;


	Rendering::Rect* srcRect = {position._x, position._y, frameW, frameH};
	Rendering::Rect* destRect = {x, y, frameW, frameH};

	/*Rendering::Rect* srcRect = {sprite.getPosX(), sprite.getPosY(), size, size};
	Rendering::Rect* destRect = {gridPosX * (size * tileScaler),
						 gridPosY * (size * tileScaler), size * tileScaler,
						 size * tileScaler};*/

	/*registry.emplace<SpriteComponent>(
		player, texture, srcRect, destRect, frameW, frameH, frameCount,
		currentFrame, SDL_GetTicks(), animationSpeed, frameRowUp, frameRowDown,
		frameRowLeft, frameRowRight, movementSpeed, moveInterval);*/


	Rendering::RendererFlip flip = flipX ? Rendering::FLIP_HORIZONTAL : Rendering::FLIP_NONE;
	Rendering::RenderCopyEx(renderer, _texture, srcRect, destRect, 0, NULL, flip);

	/*SDL_RenderClear(renderer);

	registry.view<SpriteComponent>().each(
		[&](auto& sprite)
		{
			SDL_RendererFlip flip =
				((sprite.facingDirection == SpriteComponent::RIGHT &&
				  sprite.frameRowRight == 0) ||
				 (sprite.facingDirection == SpriteComponent::LEFT &&
				  sprite.frameRowLeft == 0))
					? SDL_FLIP_HORIZONTAL
					: SDL_FLIP_NONE;
			SDL_RenderCopyEx(renderer, sprite.texture, &sprite.srcRect,
							 &sprite.destRect, 0, NULL, flip);
		});

	SDL_RenderPresent(renderer);*/
}

void Sprite::FlipHorizontally() 
{
	flipX = !flipX;
}

void Sprite::FlipVertically() 
{
	flipY = !flipY;
}
