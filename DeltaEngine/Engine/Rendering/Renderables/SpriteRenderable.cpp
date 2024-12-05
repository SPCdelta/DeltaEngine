#include "SpriteRenderable.hpp"


SpriteRenderable::SpriteRenderable(const std::string& spriteName)
	: _spriteName{spriteName}, _animator{nullptr}, _sheet{nullptr}
{
	_spriteData = ResourceManager::Get(spriteName);
}

SpriteRenderable::SpriteRenderable(const std::string& spriteName, std::shared_ptr<AnimationSheet> sheet = nullptr)
	: _spriteName(spriteName), _animator(nullptr)
{
	_animator = std::make_shared<Animator>();
	_sheet = sheet;
	_spriteData = ResourceManager::Get(spriteName);
}

void SpriteRenderable::SetSprite(const std::string& spriteName)
{
	_spriteName = spriteName;
	_spriteData = ResourceManager::Get(spriteName);
}