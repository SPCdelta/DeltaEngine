#pragma once

#include "Renderable.hpp"

#include <string>

class SpriteRenderable : public Renderable
{
public:
	SpriteRenderable(const std::string& spriteName);
	SpriteRenderable(const std::string& spriteName, std::shared_ptr<AnimationSheet> sheet);

	void SetSprite(const std::string& spriteName);

	const std::string& GetSprite() const;
	SpriteData* GetSpriteData() const;

	std::shared_ptr<Animator> GetAnimator() const;
	std::shared_ptr<AnimationSheet> GetSheet() const;

	bool GetVisible() const;
	void SetVisible(bool visible_);

protected:
	std::string _spriteName;
	SpriteData* _spriteData;

	std::shared_ptr<Animator> _animator;
	std::shared_ptr<AnimationSheet> _sheet;

	bool _visible{true};
};
