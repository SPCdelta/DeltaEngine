#pragma once

#include "Rendering.hpp"

struct SpriteComponent
{
	Rendering::Texture* texture;

	Rendering::Rect srcRect;
	Rendering::Rect destRect;

	int frameWidth;
	int frameHeight;
	int frameCount;
	int currentFrame;

	Rendering::UnsignInt32 lastFrameTime;
	Rendering::UnsignInt32 animationSpeed;

	int frameRowUp;
	int frameRowDown;
	int frameRowLeft;
	int frameRowRight;

	int movementSpeed;
	Rendering::UnsignInt32 moveInterval;

	bool hasAttackAnimation = false;
	int attackFrameCount;
	int attackCurrentFrame;
	Rendering::UnsignInt32 attackAnimationSpeed;
	int attackRow;
	bool isAttacking = false;

	bool hasIdleAnimation = false;
	int idleFrameCount;
	int idleCurrentFrame;
	Rendering::UnsignInt32 idleAnimationSpeed;
	int idleRow;

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	} 
	
	facingDirection = RIGHT;
};