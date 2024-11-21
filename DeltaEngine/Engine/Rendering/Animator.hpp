#pragma once

#include <vector>
#include <memory>

#include "../Core/Math/Vector2.hpp"
#include "Rendering.hpp"
#include "SpriteSheet.hpp"

class Animator
{
public:
	Animator();
	~Animator();

	void Play(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet, int viewportHeight, Direction direc);

	void MoveUp(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet);
	void MoveDown(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet);
	void MoveLeft(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet);
	void MoveRight(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet);

	void StandIdle(Rendering::UnsignInt32 currentTime, std::shared_ptr<SpriteSheet> sheet);

private:

};
