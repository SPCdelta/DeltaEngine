#pragma once

#include "Rendering.hpp"

// Position Component
struct PositionComponent
{
	int x;
	int y;
};

// Sprite Component
struct SpriteComponent
{
	SDL_Texture* texture;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	int frameWidth;
	int frameHeight;
	int frameCount;
	int currentFrame;

	Uint32 lastFrameTime;
	Uint32 animationSpeed;

	int frameRowUp;
	int frameRowDown;
	int frameRowLeft;
	int frameRowRight;

	int movementSpeed;
	Uint32 moveInterval;

	bool hasAttackAnimation = false;
	int attackFrameCount;
	int attackCurrentFrame;
	Uint32 attackAnimationSpeed;
	int attackRow;
	bool isAttacking = false;

	bool hasIdleAnimation = false;
	int idleFrameCount;
	int idleCurrentFrame;
	Uint32 idleAnimationSpeed;
	int idleRow;

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	} facingDirection = RIGHT;
};
