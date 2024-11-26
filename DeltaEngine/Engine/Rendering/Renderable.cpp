#include "Renderable.hpp"

Renderable::Renderable(const char* spritePath)
	: sprite{spritePath}, _texture{nullptr}, _animator{nullptr}, _sheet{nullptr}
{
}

Renderable::Renderable(const char* spritePath,
					   std::shared_ptr<SpriteSheet> sheet = nullptr)
	: sprite(spritePath), _texture(nullptr), _animator(nullptr)
{
	_animator = std::make_shared<Animator>();
	_sheet = sheet;
}

Renderable::~Renderable()
{
	StopRendering();
	_texture = nullptr;
}

Renderable::Renderable(const Renderable& other)
	: sprite(other.sprite),
	  color(other.color),
	  flipX(other.flipX),
	  flipY(other.flipY),
	  _texture(other._texture),
	  _animator(other._animator),
	  _sheet(other._sheet)
{
}

Renderable& Renderable::operator=(const Renderable& other)
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

Renderable::Renderable(Renderable&& other) noexcept
	: sprite(other.sprite),
	  _texture(other._texture),
	  color(other.color),
	  flipX(other.flipX),
	  flipY(other.flipY),
	  _animator(other._animator),
	  _sheet(other._sheet)
{
	other._texture = nullptr;
	other._animator = nullptr;
	other._sheet = nullptr;
}

Renderable& Renderable::operator=(Renderable&& other) noexcept
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

void Renderable::StopRendering()
{
	if (_texture)
		Rendering::DestroyTexture(_texture);
}

Rendering::Color Renderable::GetColor() const
{
	return color;
}

void Renderable::SetColor(Rendering::Color newColor)
{
	color = newColor;
}

Rendering::Texture* Renderable::GetTexture()
{
	return _texture;
}
