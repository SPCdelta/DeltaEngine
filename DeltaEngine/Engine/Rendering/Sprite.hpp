#pragma once

#include "Rendering.hpp"
#include "../Core/Math/Vector2.hpp"

#include <iostream>

#include <string>

class Sprite
{
public:
	Sprite(std::string spritePath);
	~Sprite();

	// TODO rule of 5

	void Render(Rendering::Renderer* renderer, Math::Vector2 position);

	void FlipHorizontally();
	void FlipVertically();

private:
	std::string sprite;

	Rendering::Texture* _texture;

	Rendering::Color color; // TODO right type?

	bool flipX{false};
	bool flipY{false};

	/*sortingLayer;
	orderInLayer;*/
};