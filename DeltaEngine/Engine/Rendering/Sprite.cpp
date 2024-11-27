#include "Sprite.hpp"

Sprite::Sprite(const char* spritePath) 
	: sprite{spritePath}, _texture{nullptr}, _animator{nullptr}, _sheet{ nullptr }
{

}

Sprite::Sprite(const char* spritePath, std::shared_ptr<SpriteSheet> sheet) : sprite(spritePath), _texture(nullptr), _animator(nullptr), _sheet(nullptr)
{
	_animator = std::make_shared<Animator>();
	_sheet = sheet;
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

void Sprite::Render(Rendering::Renderer* renderer, const ViewportData& viewportData, const Camera* camera, const Transform& transform)
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
	destRect.x = static_cast<int>((transform.position.GetX() - camera->transform.position.GetX()) * viewportData.unitPixelSize);
	destRect.y = static_cast<int>(viewportData.height - ((transform.position.GetY() - camera->transform.position.GetY()) * viewportData.unitPixelSize) - (transform.scale.GetY() * viewportData.unitPixelSize));

	destRect.w = (static_cast<int>(transform.scale.GetX()) * viewportData.unitPixelSize);
	destRect.h = (static_cast<int>(transform.scale.GetY()) * viewportData.unitPixelSize);

	if (_sheet)
	{
		Rendering::Rect srcRect = _sheet->GetSrcRect();
		Rendering::RenderCopyEx(renderer, _texture, &srcRect, &destRect, transform.rotation, 0, 
			Rendering::GetFlip((
				(_sheet->GetFacingDirection() == Direction::RIGHT && _sheet->GetRowRight() == 0)
				|| (_sheet->GetFacingDirection() == Direction::LEFT && _sheet->GetRowLeft() == 0)
				|| (flipX)), flipY)
		);
	}
	else
	{
		Rendering::RenderCopyEx(renderer, _texture, NULL, &destRect, transform.rotation, 0, Rendering::GetFlip(flipX, flipY));
	}
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
