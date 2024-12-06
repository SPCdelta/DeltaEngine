#pragma once
#include "Renderable.hpp"
#include <string>

class SpriteRenderable : public Renderable
{
   public:
	SpriteRenderable(const std::string& spriteName);
	SpriteRenderable(const std::string& spriteName, std::shared_ptr<AnimationSheet> sheet);

	void SetSprite(const std::string& spriteName);

	const std::string& GetSprite() const { return _spriteName; }
	SpriteData* GetSpriteData() const { return _spriteData; }

	std::shared_ptr<Animator> GetAnimator() const { return _animator; }
	std::shared_ptr<AnimationSheet> GetSheet() const { return _sheet; }

protected:
	std::string _spriteName;
	SpriteData* _spriteData;

	std::shared_ptr<Animator> _animator;
	std::shared_ptr<AnimationSheet> _sheet;

};
