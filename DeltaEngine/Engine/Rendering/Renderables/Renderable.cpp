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

void Renderable::RenderBorder(Rendering::Renderer* renderer, Rendering::Rect& borderRect)
{
	if (borderThickness > 0) {
		Rendering::SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		Rendering::RenderFillRect(renderer, &borderRect);
		
		borderRect.x += borderThickness;
		borderRect.y += borderThickness;
		borderRect.w -= 2 * borderThickness;
		borderRect.h -= 2 * borderThickness;
	}
}
