#include "Sprite.hpp"

Sprite::Sprite(const char* spritePath) : sprite(spritePath), _texture(nullptr)
{

}

Sprite::~Sprite()
{
	StopRendering();
	_texture = nullptr;
}

Sprite::Sprite(const Sprite& other) : sprite(other.sprite), color(other.color), flipX(other.flipX), flipY(other.flipY)
{
	if (other._texture)
		_texture = other._texture;
}

Sprite& Sprite::operator=(const Sprite& other)
{
	if (this == &other)
	{
		StopRendering();

		sprite = other.sprite;
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;

		if (other._texture)
			_texture = other._texture;
	}

	return *this;
}

Sprite::Sprite(Sprite&& other) noexcept : sprite(other.sprite), _texture(other._texture), color(other.color), flipX(other.flipX), flipY(other.flipY)
{
	other._texture = nullptr;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
	if (this != &other)
	{
		StopRendering();

		sprite = other.sprite;
		_texture = other._texture;
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;

		other._texture = nullptr;
	}

	return *this;
}

void Sprite::Render(Rendering::Renderer* renderer, Math::Vector2 position, Math::Vector2 scale, int height)
{
	Rendering::Texture* texture = Rendering::LoadTexture(renderer, sprite);
	if (!texture)
	{
		std::cerr << "Failed to load texture: " << Rendering::GetError() << std::endl;
		return; 
	}

	_texture = texture;

	int flippedY = height - position.GetY() - scale.GetY(); 

	Rendering::Rect srcRect = {0, 0, scale.GetX(), scale.GetY()};
	Rendering::Rect destRect = {position.GetX(), flippedY, scale.GetX(), scale.GetY()}; 

	Rendering::RendererFlip flip = flipX ? Rendering::FLIP_HORIZONTAL : Rendering::FLIP_NONE;

	Rendering::RenderCopyEx(renderer, _texture, &srcRect, &destRect, 0, NULL, flip);
	Rendering::RenderPresent(renderer);
}

void Sprite::StopRendering()
{
	if (_texture)
		Rendering::DestroyTexture(_texture);
}

Rendering::Color Sprite::GetColor() const
{
	return color;
}

void Sprite::SetColor(Rendering::Color newColor) 
{
	color = newColor;
}

void Sprite::FlipHorizontally() 
{
	flipX = !flipX;
}

void Sprite::FlipVertically() 
{
	flipY = !flipY;
}
