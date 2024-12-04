#include "Renderable.hpp"

//Renderable::Renderable(const char* spriteName) 
//	: _spriteName{spriteName}, _animator{nullptr}, _sheet{nullptr}
//{
//	_spriteData = ResourceManager::Get(spriteName);
//}
//
//Renderable::Renderable(const char* spriteName, std::shared_ptr<AnimationSheet> sheet = nullptr)
//	: _spriteName(spriteName), _animator(nullptr)
//{
//	_animator = std::make_shared<Animator>();
//	_sheet = sheet;
//	_spriteData = ResourceManager::Get(spriteName);
//}

Renderable::Renderable(const Renderable& other) : 
		//_spriteName(other._spriteName),
	  color(other.color),
	  flipX(other.flipX),
	  flipY(other.flipY)
	  /*_spriteData(other._spriteData),
	  _animator(other._animator),
	  _sheet(other._sheet)*/
{

}

Renderable& Renderable::operator=(const Renderable& other)
{
	if (this == &other)
	{
		//_spriteName = other._spriteName;
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;

		/*_spriteData = other._spriteData;
		_animator = other._animator;
		_sheet = other._sheet;*/
	}

	return *this;
}

Renderable::Renderable(Renderable&& other) noexcept
	: /*_spriteName(other._spriteName),
	  _spriteData(other._spriteData),*/
	  color(other.color),
	  flipX(other.flipX),
	  flipY(other.flipY)
	  /*_animator(other._animator),
	  _sheet(other._sheet)*/
{
	//other._animator = nullptr;
	//other._sheet = nullptr;
}

Renderable& Renderable::operator=(Renderable&& other) noexcept
{
	if (this != &other)
	{
		//_spriteName = other._spriteName;
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;

		/*_spriteData = other._spriteData;
		_animator = other._animator;
		_sheet = other._sheet;*/

		/*other._spriteData = nullptr;
		other._animator = nullptr;
		other._sheet = nullptr;*/
	}

	return *this;
}

Rendering::Color Renderable::GetColor() const
{
	return color;
}

void Renderable::SetColor(Rendering::Color newColor)
{
	color = newColor;
}
