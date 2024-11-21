#include "Sprite.hpp"

Sprite::Sprite(const char* spritePath, std::shared_ptr<SpriteSheet> sheet) : sprite(spritePath), _texture(nullptr), _animator(nullptr), _sheet(nullptr)
{
	if (sheet)
	{
		_animator = std::make_shared<Animator>();
		_sheet = sheet;
	}
}

Sprite::~Sprite()
{
	StopRendering();
	_texture = nullptr;
}

Sprite::Sprite(const Sprite& other) : sprite(other.sprite), color(other.color), flipX(other.flipX), flipY(other.flipY), _texture(other._texture), 
	_animator(other._animator), _sheet(other._sheet)
{

}

Sprite& Sprite::operator=(const Sprite& other)
{
	if (this == &other)
	{
		StopRendering();
		_texture = nullptr;

		sprite = other.sprite;
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;

		_texture = other._texture;
		_animator = other._animator;
		_sheet = other._sheet;
	}

	return *this;
}

Sprite::Sprite(Sprite&& other) noexcept : sprite(other.sprite), _texture(other._texture), color(other.color), flipX(other.flipX), flipY(other.flipY),
	  _animator(other._animator), _sheet(other._sheet)
{
	other._texture = nullptr;
	other._animator = nullptr;
	other._sheet = nullptr;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
	if (this != &other)
	{
		StopRendering();
		_texture = nullptr;

		sprite = other.sprite;
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;

		_texture = other._texture;
		_animator = other._animator;
		_sheet = other._sheet;

		other._texture = nullptr;
		other._animator = nullptr;
		other._sheet = nullptr;
	}

	return *this;
}

void Sprite::Render(Rendering::Renderer* renderer, Math::Vector2* position, int height)
{
	Rendering::Texture* texture = Rendering::LoadTexture(renderer, sprite);
	if (!texture)
	{
		std::cerr << "Failed to load texture: " << Rendering::GetError() << std::endl;
		return;
	}

	_texture = texture;

	Rendering::Rect srcRect, destRect; 
	if (_sheet)
	{
		srcRect = _sheet->GetSrcRect();
		destRect = _sheet->GetDestRect(); 
		SetFlipX(((_sheet->GetFacingDirection() == Direction::RIGHT && _sheet->GetRowRight() == NULL) || (_sheet->GetFacingDirection() == Direction::LEFT &&
		  _sheet->GetRowLeft() == NULL)));
	}
	else // TODO magic nums \/
	{
		int flippedY = height - position->GetY() - 64;
		srcRect = {0, 0, 64, 64};
		destRect = {static_cast<int>(round(position->GetX())), flippedY, 64, 64}; 
	}

	Rendering::RendererFlip flip = flipX ? Rendering::FLIP_HORIZONTAL : Rendering::FLIP_NONE;
	Rendering::RenderCopyEx(renderer, _texture, &srcRect, &destRect, 0, NULL, flip);
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

Rendering::Texture* Sprite::GetTexture()
{
	return _texture;
}
