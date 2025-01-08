#include "Renderable.hpp"

Renderable::Renderable(const Renderable& other) 
	: color(other.color),
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

void Renderable::SetFlipX(bool flip)
{
	flipX = flip;
}

void Renderable::SetFlipY(bool flip)
{
	flipY = flip;
}

Layer Renderable::GetLayer() const
{
	return _layer;
}

void Renderable::SetLayer(Layer layer)
{
	_layer = layer;
}

void Renderable::SetBorder(uint16_t borderThickness_)
{
	borderThickness = borderThickness_;
}

void Renderable::SetBorderColor(Rendering::Color borderColor_)
{
	borderColor = borderColor_;
}

void Renderable::RemoveBorder()
{
	borderThickness = 0;
}

void Renderable::RenderBorder(Rendering::Renderer* renderer, Rendering::Rect& borderRect) const
{
	if (borderThickness > 0) 
	{
		Rendering::SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		Rendering::RenderFillRect(renderer, &borderRect);
		
		borderRect.x += borderThickness;
		borderRect.y += borderThickness;
		borderRect.w -= 2 * borderThickness;
		borderRect.h -= 2 * borderThickness;
	}
}
