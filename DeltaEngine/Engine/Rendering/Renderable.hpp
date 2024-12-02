#pragma once

#include "../Core/Math/Vector2.hpp"

#include "Managers.hpp"
#include "Rendering.hpp"
#include "Animator.hpp"
#include "SpriteSheet.hpp"
#include "Viewport.hpp"
#include "Camera.hpp"
#include "Layer.hpp"
#include <iostream>

#include <string>

class Renderable
{
public:
	Renderable(const char* spriteName);
	Renderable(const char* spriteName, std::shared_ptr<SpriteSheet> sheet);

	Renderable(const Renderable& other);
	Renderable& operator=(const Renderable& other);

	Renderable(Renderable&& other) noexcept;
	Renderable& operator=(Renderable&& other) noexcept;

	// will break oopsie poopsie
	const char* GetPath() const { return _spriteName; }

	const char* GetSprite() const { return _spriteName; }
	SpriteData* GetSpriteData() const { return _spriteData; }

	Rendering::Color GetColor() const;
	void SetColor(Rendering::Color newColor);

	void SetFlipX(bool flip) { flipX = flip; };
	void SetFlipY(bool flip) { flipY = flip; };

	Layer GetLayer() const { return _layer; };
	void SetLayer(Layer layer) { _layer = layer; };

	std::shared_ptr<Animator> GetAnimator() const { return _animator; }
	std::shared_ptr<SpriteSheet> GetSheet() const { return _sheet; }

protected:
	const char* _spriteName;
	SpriteData* _spriteData;

	std::shared_ptr<Animator> _animator;
	std::shared_ptr<SpriteSheet> _sheet;

	Rendering::Color color{Rendering::Color(255, 255, 255, 255)};

	bool flipX{false};
	bool flipY{false};

	Layer _layer{ Layer::Default };
};