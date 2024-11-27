#pragma once

#include <vector>
#include <memory>

#include "../Core/Math/Vector2.hpp"
#include "Rendering.hpp"
#include "SpriteSheet.hpp"

class Animator
{
public:
	void Play(std::shared_ptr<SpriteSheet> sheet, Direction direc);

	void MoveUp(std::shared_ptr<SpriteSheet> sheet);
	void MoveDown(std::shared_ptr<SpriteSheet> sheet);
	void MoveLeft(std::shared_ptr<SpriteSheet> sheet);
	void MoveRight(std::shared_ptr<SpriteSheet> sheet);

	void StandIdle(Rendering::UnsignInt32 currentTime, std::shared_ptr<SpriteSheet> sheet);

private:

};
