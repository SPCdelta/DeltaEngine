#include "AnimationSheet.hpp"
#include "../Core/Time.hpp"

AnimationSheet::AnimationSheet(Transform& transform, int framesInRow, int frameW, int frameH, int rowUp, int rowDown, int rowLeft, int rowRight) 
	: frameCount(framesInRow), 
	  frameRowUp(rowUp), 
	  frameRowDown(rowDown), 
	  frameRowLeft(rowLeft), 
	  frameRowRight(rowRight), 
	  frameWidth(frameW), 
	  frameHeight(frameH)
{
	int flippedY = 0 - static_cast<int>(transform.position.GetY()) - frameHeight;

	Rendering::Rect src = {0, 0, frameWidth, frameHeight};
	Rendering::Rect dest = { static_cast<int>(transform.position.GetX()), flippedY, frameWidth, frameHeight};

	srcRect = src;
	destRect = dest;
}

int AnimationSheet::GetCurrentFrame() const
{
	return currentFrame;
}

void AnimationSheet::SetCurrentFrame(int newFrame)
{
	currentFrame = newFrame;
}

int AnimationSheet::GetFrameCount() const
{
	return frameCount;
}

float AnimationSheet::GetMovementSpeed() const
{
	return movementSpeed;
}

int AnimationSheet::GetAnimationSpeed() const
{
	return animationSpeed;
}

int AnimationSheet::GetFrameWidth() const
{
	return frameWidth;
}

int AnimationSheet::GetFrameHeight() const
{
	return frameHeight;
}

int AnimationSheet::GetRowUp() const
{
	return frameRowUp;
}

int AnimationSheet::GetRowDown() const
{
	return frameRowDown;
}

int AnimationSheet::GetRowLeft() const
{
	return frameRowLeft;
}

int AnimationSheet::GetRowRight() const
{
	return frameRowRight;
}

Rendering::Rect AnimationSheet::GetSrcRect() const
{
	return srcRect;
}

void AnimationSheet::SetSrcRect(Rendering::Rect src)
{
	srcRect = src;
}

Rendering::Rect AnimationSheet::GetDestRect() const
{
	return destRect;
}

void AnimationSheet::SetDestRect(Rendering::Rect dest)
{
	destRect = dest;
}

Rendering::Rect AnimationSheet::GetPrevDestRect() const
{
	return prevDestRect;
}

void AnimationSheet::SetPrevDestRect(Rendering::Rect prev)
{
	prevDestRect = prev;
}

Rendering::UnsignInt32 AnimationSheet::GetLastMoveTime() const
{
	return lastMoveTime;
}

void AnimationSheet::SetLastMoveTime(Rendering::UnsignInt32 time)
{
	lastMoveTime = time;
}

Rendering::UnsignInt32 AnimationSheet::GetLastFrameTime() const
{
	return lastFrameTime;
}

void AnimationSheet::SetLastFrameTime(Rendering::UnsignInt32 time)
{
	lastFrameTime = time;
}

Rendering::UnsignInt32 AnimationSheet::GetMoveInterval() const
{
	return moveInterval;
}

void AnimationSheet::AddIdleAnimation(int frameCount, int row, Rendering::UnsignInt32 idleAnimSpeed)
{
	idleFrameCount = frameCount;
	idleRow = row;
	idleAnimationSpeed = idleAnimSpeed;
}

int AnimationSheet::GetIdleFrameCount() const
{
	return idleFrameCount;
}

Rendering::UnsignInt32 AnimationSheet::GetIdleAnimSpeed() const
{
	return idleAnimationSpeed;
}

int AnimationSheet::GetIdleRow() const
{
	return idleRow;
}

int AnimationSheet::GetIdleCurrentFrame() const
{
	return idleCurrentFrame;
}

void AnimationSheet::SetIdleCurrentFrame(int newFrame)
{
	idleCurrentFrame = newFrame;
}

Direction AnimationSheet::GetFacingDirection() const
{
	return facingDirection;
}

void AnimationSheet::SetFacingDirection(Direction direction)
{
	facingDirection = direction;
}

void AnimationSheet::AddCustomAnimation(const std::string& animationName, int frameCount, int row, Rendering::UnsignInt32 animSpeed)
{
	customAnimations[animationName] = {frameCount, row, animSpeed};
}

bool AnimationSheet::PlayCustomAnimation(const std::string& animationName)
{
	Rendering::UnsignInt32 currentTime = static_cast<Rendering::UnsignInt32>(Time::GetDeltaTime());
	if (customAnimations.find(animationName) == customAnimations.end())
		return false;
	
	const AnimationData& animData = customAnimations[animationName];
	if (currentTime - lastFrameTime < animData.animSpeed)
		return false;
	
	currentFrame = (currentFrame + 1) % animData.frameCount;
	srcRect.y = (animData.row - 1) * frameHeight;
	srcRect.x = currentFrame * frameWidth;
	lastFrameTime = currentTime;

	// If true, animation still playing
	// If false, animation is done playing
	if ((currentFrame + 1) == animData.frameCount) 
		return false;
	else
		return true;
}
