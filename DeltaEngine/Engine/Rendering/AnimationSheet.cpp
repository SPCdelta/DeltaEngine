#include "AnimationSheet.hpp"
#include "../Core/Time.hpp"

AnimationSheet::AnimationSheet(Transform& transform, int framesInRow, int frameW, int frameH, int rowUp, int rowDown, 
	int rowLeft, int rowRight) : frameCount(framesInRow), frameRowUp(rowUp), frameRowDown(rowDown), frameRowLeft(rowLeft), 
	frameRowRight(rowRight), frameWidth(frameW), frameHeight(frameH)
{
	int flippedY = 0 - transform.position.GetY() - frameHeight; 
	Rendering::Rect src = {0, 0, frameWidth, frameHeight};
	Rendering::Rect dest = {transform.position.GetX(), flippedY, frameWidth, frameHeight};

	srcRect = src;
	destRect = dest;
}

void AnimationSheet::AddIdleAnimation(int frameCount, int row, Rendering::UnsignInt32 idleAnimSpeed)
{
	idleFrameCount = frameCount;
	idleRow = row;
	idleAnimationSpeed = idleAnimSpeed;
}

void AnimationSheet::AddCustomAnimation(const std::string& animationName, int frameCount, int row, Rendering::UnsignInt32 animSpeed)
{
	customAnimations[animationName] = {frameCount, row, animSpeed};
}

bool AnimationSheet::PlayCustomAnimation(const std::string& animationName)
{
	Rendering::UnsignInt32 currentTime = Time::GetDeltaTime();
	if (customAnimations.find(animationName) != customAnimations.end())
	{
		const AnimationData& animData = customAnimations[animationName];
		if (currentTime - lastFrameTime > animData.animSpeed)
		{
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
	}
}
