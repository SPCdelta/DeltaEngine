#include "Renderable.hpp"

Renderable::Renderable(const Renderable& other) : 
	  color(other.color),
	  flipX(other.flipX),
	  flipY(other.flipY)
{

}

Renderable& Renderable::operator=(const Renderable& other)
{
	if (this == &other)
	{
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;
	}

	return *this;
}

Renderable::Renderable(Renderable&& other) noexcept
	: color(other.color),
	  flipX(other.flipX),
	  flipY(other.flipY)
{
}

Renderable& Renderable::operator=(Renderable&& other) noexcept
{
	if (this != &other)
	{
		color = other.color;
		flipX = other.flipX;
		flipY = other.flipY;

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
