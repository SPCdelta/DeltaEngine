#include "Animator.hpp"

Animator::Animator(const char* spritePath)
{
	// TODO
}

Animator::~Animator()
{
	// TODO
}

void Animator::Play()
{
	/*void Game::createPlayer(
		int x, int y, const char* texturePath, int frameW, int frameH,
		int frameCount, int currentFrame, Uint32 animationSpeed, int frameRowUp,
		int frameRowDown, int frameRowLeft, int frameRowRight,
		int movementSpeed = 5, Uint32 moveInterval = 40);*/


	// TODO

}

void Animator::Stop()
{
	// TODO

	/*void addAttackAnimation(int attackFrameCount, int attackRow, Uint32 attackAnimationSpeed);
	void addIdleAnimation(int idleFrameCount, int idleRow, Uint32 idleAnimationSpeed);*/

	void moveUp(int xPos, int yPox, SpriteComponent & sprite);
	void moveDown(int xPos, int yPox, SpriteComponent& sprite);
	void moveLeft(int xPos, int yPox, SpriteComponent& sprite);
	void moveRight(int xPos, int yPox, SpriteComponent& sprite);
	void standIdle(Uint32 currentTime, SpriteComponent & sprite);
}