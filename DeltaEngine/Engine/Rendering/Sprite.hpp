#pragma once

#include "Rendering.hpp"
#include "../Core/Math/Vector2.hpp"

#include <iostream>

#include <string>

class Sprite
{
public:
	Sprite(const char* spritePath);
	~Sprite();

	// TODO rule of 5

	void Render(Rendering::Renderer* renderer, Math::Vector2 position, Math::Vector2 scale);
	void StopRendering();

	void FlipHorizontally();
	void FlipVertically();

private:
	const char* sprite;

	Rendering::Texture* _texture;

	Rendering::Color color; // TODO right type?

	bool flipX{false};
	bool flipY{false};

	/*sortingLayer;
	orderInLayer;*/ // TODO 
};