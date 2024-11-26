#pragma once

#include "../Core/Math/Vector2.hpp"

#include "Rendering.hpp"
#include "Animator.hpp"
#include "SpriteSheet.hpp"
#include "Viewport.hpp"
#include "Camera.hpp"

#include <iostream>

#include <string>

class Renderable
{
public:
	Renderable(const char* spritePath);
	Renderable(const char*, std::shared_ptr<SpriteSheet> sheet);
	
	~Renderable();

	Renderable(const Renderable& other);
	Renderable& operator=(const Renderable& other);

	Renderable(Renderable&& other) noexcept;
	Renderable& operator=(Renderable&& other) noexcept;

	void StopRendering();

	Rendering::Color GetColor() const;
	void SetColor(Rendering::Color newColor);

	void SetFlipX(bool flip) { flipX = flip; };
	void SetFlipY(bool flip) { flipY = flip; };

	std::shared_ptr<Animator> GetAnimator() const { return _animator; }
	std::shared_ptr<SpriteSheet> GetSheet() const { return _sheet; }
	Rendering::Texture* GetTexture();

protected:
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