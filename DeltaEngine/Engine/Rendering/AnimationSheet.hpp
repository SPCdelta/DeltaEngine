#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "Rendering.hpp"
#include "..\Transform.hpp"
#include "Direction.hpp"

struct AnimationData
{
	int frameCount;
	int row;
	Rendering::UnsignInt32 animSpeed;
};

class AnimationSheet
{
public:
	AnimationSheet(Transform& transform, int framesInRow, int frameW, int frameH, int rowUp = 0, int rowDown = 0, 
		int rowLeft = 0, int rowRight = 0);
	~AnimationSheet() = default;

    void AddCustomAnimation(const std::string& animationName, int frameCount, int row, Rendering::UnsignInt32 animSpeed);
	bool PlayCustomAnimation(const std::string& animationName);

	int GetCurrentFrame() const { return currentFrame; }
	void SetCurrentFrame(int newFrame) { currentFrame = newFrame; }

	int GetFrameCount() const { return frameCount; }
	float GetMovementSpeed() const { return movementSpeed; }
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
	float movementSpeed{0.25f};
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

	int idleFrameCount;
	int idleCurrentFrame{0};
	Rendering::UnsignInt32 idleAnimationSpeed;
	int idleRow{0};

	Direction facingDirection = RIGHT;

	std::unordered_map<std::string, AnimationData> customAnimations;
};
