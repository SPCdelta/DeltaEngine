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
	AnimationSheet(Transform& transform, int framesInRow, int frameW, int frameH, int rowUp = 0, int rowDown = 0, int rowLeft = 0, int rowRight = 0);
	~AnimationSheet() = default;

    void AddCustomAnimation(const std::string& animationName, int frameCount, int row, Rendering::UnsignInt32 animSpeed);
	bool PlayCustomAnimation(const std::string& animationName);

	int GetCurrentFrame() const;
	void SetCurrentFrame(int newFrame);

	int GetFrameCount() const;
	float GetMovementSpeed() const;
	int GetAnimationSpeed() const;

	int GetFrameWidth() const;
	int GetFrameHeight() const;

	int GetRowUp() const;
	int GetRowDown() const;
	int GetRowLeft() const;
	int GetRowRight() const;

	Rendering::Rect GetSrcRect() const;
	void SetSrcRect(Rendering::Rect src);

	Rendering::Rect GetDestRect() const;
	void SetDestRect(Rendering::Rect dest);

	Rendering::Rect GetPrevDestRect() const;
	void SetPrevDestRect(Rendering::Rect prev);

	Rendering::UnsignInt32 GetLastMoveTime() const;
	void SetLastMoveTime(Rendering::UnsignInt32 time);

	Rendering::UnsignInt32 GetLastFrameTime() const;
	void SetLastFrameTime(Rendering::UnsignInt32 time);

	Rendering::UnsignInt32 GetMoveInterval() const;

	void AddIdleAnimation(int frameCount, int row, Rendering::UnsignInt32 idleAnimSpeed);
	int GetIdleFrameCount() const;
	Rendering::UnsignInt32 GetIdleAnimSpeed() const;
	int GetIdleRow() const;

	int GetIdleCurrentFrame() const;
	void SetIdleCurrentFrame(int newFrame);

	Direction GetFacingDirection() const;
	void SetFacingDirection(Direction direction);

private:
	int currentFrame{0};
	int frameCount;
	float movementSpeed{0.25f};
	int animationSpeed{100};

	int frameWidth;
	int frameHeight;

	Rendering::Rect srcRect;
	Rendering::Rect destRect;
	Rendering::Rect prevDestRect{-1,-1,-1,-1};
	
	int frameRowUp{0};
	int frameRowDown{0};
	int frameRowLeft{0};
	int frameRowRight{0};

	Rendering::UnsignInt32 lastMoveTime{0};
	Rendering::UnsignInt32 lastFrameTime{0};
	Rendering::UnsignInt32 moveInterval{40};

	int idleFrameCount{0};
	int idleCurrentFrame{0};
	Rendering::UnsignInt32 idleAnimationSpeed{0};
	int idleRow{0};

	Direction facingDirection = RIGHT;

	std::unordered_map<std::string, AnimationData> customAnimations;
};
