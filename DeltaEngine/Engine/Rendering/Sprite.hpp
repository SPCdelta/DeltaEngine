#pragma once

#include "Rendering.hpp"
#include "../Core/Math/Vector2.hpp"
#include "Animator.hpp"

#include <iostream>

#include <string>

class Sprite
{
public:
	Sprite(const char* spritePath, bool hasAnimation);
	~Sprite();

	Sprite(const Sprite& other);			 
	Sprite& operator=(const Sprite& other);	 

	Sprite(Sprite&& other) noexcept;		
	Sprite& operator=(Sprite&& other) noexcept;

	void Render(Rendering::Renderer* renderer, Math::Vector2 position, Math::Vector2 scale, int height);
	void StopRendering();

	Rendering::Color GetColor() const;
	void SetColor(Rendering::Color newColor);

	void FlipHorizontally();
	void FlipVertically();

private:
	const char* sprite;
	Animator* _animator; // TODO either has one or does not have one

	Rendering::Texture* _texture;
	Rendering::Color color{Rendering::Color(0, 0, 0, 255)};

	bool flipX{false};
	bool flipY{false};

	/*sortingLayer;
	orderInLayer;*/ // TODO wait for layer
};