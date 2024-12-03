#pragma once

#include <vector>
#include <memory>

#include "../Core/Math/Vector2.hpp"
#include "Rendering.hpp"
#include "AnimationSheet.hpp"

class Animator
{
public:
	void Play(std::shared_ptr<AnimationSheet> sheet, Direction direc, bool pauseWalk);

	void MoveUp(std::shared_ptr<AnimationSheet> sheet);
	void MoveDown(std::shared_ptr<AnimationSheet> sheet);
	void MoveLeft(std::shared_ptr<AnimationSheet> sheet);
	void MoveRight(std::shared_ptr<AnimationSheet> sheet);

	void StandIdle(Rendering::UnsignInt32 currentTime, std::shared_ptr<AnimationSheet> sheet);

private:

};
