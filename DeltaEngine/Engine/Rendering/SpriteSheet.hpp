#pragma once

#include <vector>

#include "Rendering.hpp"
#include "..\Transform.hpp"
#include "Direction.hpp"

class SpriteSheet
{
public:
	SpriteSheet(Transform& transform, int framesInRow, int frameW, int frameH, int rowUp = 0, int rowDown = 0, 
		int rowLeft = 0, int rowRight = 0);
	~SpriteSheet();

	int GetCurrentFrame() const { return currentFrame; }
	void SetCurrentFrame(int newFrame) { currentFrame = newFrame; }

	int GetFrameCount() const { return frameCount; }
	int GetMovementSpeed() const { return movementSpeed; }
	int GetAnimationSpeed() const { return animationSpeed; }

	int GetFrameWidth() const { return frameWidth; }
	int GetFrameHeight() const { return frameHeight; }

	int GetRowUp() const { return frameRowUp; }
	int GetRowDown() const { return frameRowDown; }
	int GetRowLeft() const { return frameRowLeft; }
	int GetRowRight() const { return frameRowRight; }

	Rendering::Rect GetSrcRect() const { return srcRect; }
	void SetSrcRect(Rendering::Rect src) { srcRect = src; }

	Rendering::Rect GetDestRect() const { return destRect; }
	void SetDestRect(Rendering::Rect dest) { destRect = dest; }

	Rendering::Rect GetPrevDestRect() const { return prevDestRect; }
	void SetPrevDestRect(Rendering::Rect prev) { prevDestRect = prev; }

	Rendering::UnsignInt32 GetLastMoveTime() const { return lastMoveTime; }
	void SetLastMoveTime(Rendering::UnsignInt32 time) { lastMoveTime = time; }

	Rendering::UnsignInt32 GetLastFrameTime() const { return lastFrameTime; }
	void SetLastFrameTime(Rendering::UnsignInt32 time) { lastFrameTime = time; }

	Rendering::UnsignInt32 GetMoveInterval() const { return moveInterval; }

	void AddAttackAnimation(int frameCount, int row, Rendering::UnsignInt32 attackAnimSpeed);
	int GetAttFrameCount() const { return attackFrameCount; }
	Rendering::UnsignInt32 GetAttAnimSpeed() const { return attackAnimationSpeed; }
	int GetAttRow() const { return attackRow; }

	int GetAttCurrentFrame() const { return attackCurrentFrame; }
	void SetAttCurrentFrame(int newFrame) { attackCurrentFrame = newFrame; }

	void Attack();
	int GetIsAttacking() const { return isAttacking; }
	void SetIsAttacking(bool attacking) { isAttacking = attacking; }

	void AddIdleAnimation(int frameCount, int row, Rendering::UnsignInt32 idleAnimSpeed);
	int GetIdleFrameCount() const { return idleFrameCount; }
	Rendering::UnsignInt32 GetIdleAnimSpeed() const { return idleAnimationSpeed; }
	int GetIdleRow() const { return idleRow; }

	int GetIdleCurrentFrame() const { return idleCurrentFrame; }
	void SetIdleCurrentFrame(int newFrame) { idleCurrentFrame = newFrame; }

	Direction GetFacingDirection() const { return facingDirection; }
	void SetFacingDirection(Direction direction) { facingDirection = direction; }

private:
	int currentFrame{0};
	int frameCount;
	int movementSpeed{5};
	int animationSpeed{100};

	int frameWidth;
	int frameHeight;

	Rendering::Rect srcRect;
	Rendering::Rect destRect;
	Rendering::Rect prevDestRect;
	
	int frameRowUp{0};
	int frameRowDown{0};
	int frameRowLeft{0};
	int frameRowRight{0};

	Rendering::UnsignInt32 lastMoveTime{0};
	Rendering::UnsignInt32 lastFrameTime{0};
	Rendering::UnsignInt32 moveInterval{40};

	int attackFrameCount;
	int attackCurrentFrame{0};
	Rendering::UnsignInt32 attackAnimationSpeed;
	int attackRow{0};
	bool isAttacking{false};

	int idleFrameCount;
	int idleCurrentFrame{0};
	Rendering::UnsignInt32 idleAnimationSpeed;
	int idleRow{0};

	Direction facingDirection = RIGHT;
};
