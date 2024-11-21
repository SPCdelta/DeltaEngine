#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(Transform& transform, int framesInRow, int frameW, int frameH, int rowUp, int rowDown, 
	int rowLeft, int rowRight) : frameCount(framesInRow), frameRowUp(rowUp), frameRowDown(rowDown), frameRowLeft(rowLeft), 
	frameRowRight(rowRight), frameWidth(frameW), frameHeight(frameH)
{
	int flippedY = 0 - transform.position.GetY() - frameHeight; 
	Rendering::Rect src = {0, 0, frameWidth, frameHeight};
	Rendering::Rect dest = {transform.position.GetX(), flippedY, frameWidth, frameHeight};

	srcRect = src;
	destRect = dest;
}

SpriteSheet::~SpriteSheet()
{
	
}

void SpriteSheet::AddAttackAnimation(int frameCount, int row, Rendering::UnsignInt32 attackAnimSpeed)
{
	attackFrameCount = frameCount;
	attackRow = row;
	attackAnimationSpeed = attackAnimSpeed;
}

void SpriteSheet::AddIdleAnimation(int frameCount, int row, Rendering::UnsignInt32 idleAnimSpeed)
{
	idleFrameCount = frameCount;
	idleRow = row;
	idleAnimationSpeed = idleAnimSpeed;
}

void SpriteSheet::Attack()
{
	SetIsAttacking(true);
	SetAttCurrentFrame(0);
}
