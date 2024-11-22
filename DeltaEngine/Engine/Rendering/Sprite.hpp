#pragma once

#include "Rendering.hpp"
#include "../Core/Math/Vector2.hpp"
#include "Animator.hpp"
#include "SpriteSheet.hpp"

#include <iostream>

#include <string>

class Sprite
{
public:
	Sprite(const char* spritePath, std::shared_ptr<SpriteSheet> sheet);
	~Sprite();

	Sprite(const Sprite& other);			 
	Sprite& operator=(const Sprite& other);	 

	Sprite(Sprite&& other) noexcept;		
	Sprite& operator=(Sprite&& other) noexcept;

	void Render(Rendering::Renderer* renderer, Math::Vector2* position, int height);
	void StopRendering();

	Rendering::Color GetColor() const;
	void SetColor(Rendering::Color newColor);

	void SetFlipX(bool flip) { flipX = flip; };
	void SetFlipY(bool flip) { flipY = flip; };

	std::shared_ptr<Animator> GetAnimator() const { return _animator; }
	std::shared_ptr<SpriteSheet> GetSheet() const { return _sheet; }
	Rendering::Texture* GetTexture();

private:
	const char* sprite;
	std::shared_ptr<Animator> _animator;
	std::shared_ptr<SpriteSheet> _sheet;
	
	Rendering::Texture* _texture;
	Rendering::Color color{Rendering::Color(0, 0, 0, 255)};

	bool flipX{false};
	bool flipY{false};

	/*sortingLayer;
	orderInLayer;*/ // TODO wait for layer
};