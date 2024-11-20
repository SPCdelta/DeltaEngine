#pragma once

#include <vector>

#include "../Core/Math/Vector2.hpp"
#include "Rendering.hpp"
#include "SpriteSheet.hpp"

class Animator
{
public:
	Animator(const char* spritePath);
	~Animator();

	void Play(Math::Vector2* pos, SpriteSheet* sheet, int viewportHeight, Direction direc);

	void MoveUp(Math::Vector2* pos, SpriteSheet* sheet);
	void MoveDown(Math::Vector2* pos, SpriteSheet* sheet);
	void MoveLeft(Math::Vector2* pos, SpriteSheet* sheet);
	void MoveRight(Math::Vector2* pos, SpriteSheet* sheet);

	void StandIdle(Rendering::UnsignInt32 currentTime, SpriteSheet* sheet);

private:

};
