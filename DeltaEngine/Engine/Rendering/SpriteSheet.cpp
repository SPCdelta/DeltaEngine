#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(Transform* transform, int viewportHeight, int framesInRow, int animateSpeed, int frameW, int frameH, int rowUp, int rowDown, 
	int rowLeft, int rowRight) : frameCount(framesInRow), frameRowUp(rowUp), frameRowDown(rowDown), frameRowLeft(rowLeft), 
	frameRowRight(rowRight), animationSpeed(animateSpeed), frameWidth(frameW), frameHeight(frameH)
{
	int flippedY = viewportHeight - transform->position.GetY() - frameHeight; 
	Rendering::Rect src = {0, 0, frameWidth, frameHeight};
	Rendering::Rect dest = {transform->position.GetX(), flippedY, frameWidth, frameHeight};

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

//void SpriteSheet::InitSpriteSet(Transform transform)
//{
//	Math::Vector2 pos = transform.position;
//	Math::Vector2 sca = transform.scale;
//
//	/*int spriteSetWidth, spriteSetHeight;
//	Rendering::QueryTexture(_texture, nullptr, nullptr, &spriteSetWidth, &spriteSetHeight);
//
//	int spritesPerRow = spriteSetWidth / sca.GetX();
//	int spritesPerCol = spriteSetHeight / sca.GetY();*/
//
//	/*for (int y = 0; y < spritesPerCol; ++y)
//	{
//		for (int x = 0; x < spritesPerRow; ++x)
//		{
//			sprites.emplace_back(x * tileSize, y * tileSize);
//		}
//	}*/
//}
