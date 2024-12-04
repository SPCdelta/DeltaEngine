#pragma once

#include "../Core/Math/Vector2.hpp"

#include "ResourceManager.hpp"
#include "Rendering.hpp"
#include "Animator.hpp"
#include "AnimationSheet.hpp"
#include "Viewport.hpp"
#include "Camera.hpp"
#include "Layer.hpp"
#include <iostream>

#include <string>

class Renderable
{
public:
	Renderable(const char* spriteName);
	Renderable(const char* spriteName, std::shared_ptr<AnimationSheet> sheet);

	Renderable(const Renderable& other);
	Renderable& operator=(const Renderable& other);

	Renderable(Renderable&& other) noexcept;
	Renderable& operator=(Renderable&& other) noexcept;

	const char* GetSprite() const { return _spriteName; }
	SpriteData* GetSpriteData() const { return _spriteData; }

	Rendering::Color GetColor() const;
	void SetColor(Rendering::Color newColor);

	void SetFlipX(bool flip) { flipX = flip; };
	void SetFlipY(bool flip) { flipY = flip; };

	Layer GetLayer() const { return _layer; };
	void SetLayer(Layer layer) { _layer = layer; };

	void SetSprite(const std::string& spriteName);

	std::shared_ptr<Animator> GetAnimator() const { return _animator; }
	std::shared_ptr<AnimationSheet> GetSheet() const { return _sheet; }

protected:
	const char* _spriteName;
	SpriteData* _spriteData;

	std::shared_ptr<Animator> _animator;
	std::shared_ptr<AnimationSheet> _sheet;

	Rendering::Color color{Rendering::Color(255, 255, 255, 255)};

	bool flipX{false};
	bool flipY{false};

	Layer _layer{ Layer::Default };
};