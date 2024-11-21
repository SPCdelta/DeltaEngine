#include "Animator.hpp"

Animator::Animator()
{
	
}

Animator::~Animator()
{
	
}

void Animator::Play(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet, int viewportHeight, Direction direc)
{
	bool isMoving = true;
	Rendering::UnsignInt32 currentTime = Rendering::GetTicks();	

	if (sheet->GetIsAttacking() && sheet->GetAttRow() != 0 && currentTime - sheet->GetLastFrameTime() > sheet->GetAttAnimSpeed())
	{
		sheet->SetAttCurrentFrame(sheet->GetAttCurrentFrame() + 1);
		if (sheet->GetAttCurrentFrame() >= sheet->GetAttFrameCount())
		{
			sheet->SetIsAttacking(false);
			sheet->SetAttCurrentFrame(0);
		}

		Rendering::Rect tempSrcRect = sheet->GetSrcRect();
		tempSrcRect.y = (sheet->GetAttRow() - 1) * sheet->GetFrameHeight();
		tempSrcRect.x = sheet->GetAttCurrentFrame() * sheet->GetFrameWidth();
		sheet->SetSrcRect(tempSrcRect);

		sheet->SetLastFrameTime(currentTime);
	}
	else if (sheet->GetAttRow() == 0)
	{
		sheet->SetIsAttacking(false);
	}

	if (!sheet->GetIsAttacking() && currentTime - sheet->GetLastMoveTime() >= sheet->GetMoveInterval())
	{
		if (direc == Direction::UP && pos->GetY() < viewportHeight - sheet->GetDestRect().h) // up 
			MoveUp(pos, sheet);
		else if (direc == Direction::LEFT && pos->GetX() > 0)  // left
			MoveLeft(pos, sheet);
		else if (direc == Direction::DOWN && pos->GetY() > 0)  // down
			MoveDown(pos, sheet);
		else if (direc == Direction::RIGHT && pos->GetX() < viewportHeight - sheet->GetDestRect().w) // right
			MoveRight(pos, sheet);
		else
			isMoving = false;

		if (isMoving && currentTime - sheet->GetLastFrameTime() > sheet->GetAnimationSpeed())
		{
			sheet->SetCurrentFrame((sheet->GetCurrentFrame() + 1) % sheet->GetFrameCount());
			Rendering::Rect tempSrcRect = sheet->GetSrcRect();
			tempSrcRect.x = sheet->GetCurrentFrame() * sheet->GetFrameWidth();
			sheet->SetSrcRect(tempSrcRect);
			sheet->SetLastFrameTime(currentTime);
		}
		else if (!isMoving)
		{
			StandIdle(currentTime, sheet);
		}

		sheet->SetLastMoveTime(currentTime);
	}

	int flippedY = viewportHeight - pos->GetY() - sheet->GetFrameHeight(); 
	Rendering::Rect tempDestRect = sheet->GetDestRect();
	tempDestRect.x = pos->GetX();
	tempDestRect.y = flippedY;
	sheet->SetDestRect(tempDestRect);
}

void Animator::MoveUp(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet)
{
	pos->SetY(pos->GetY() + sheet->GetMovementSpeed());
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();

	if (sheet->GetFacingDirection() == Direction::LEFT)
	{
		tempSrcRect.y = (sheet->GetRowUp() ? (sheet->GetRowUp() - 1) : (sheet->GetRowLeft() ? (sheet->GetRowLeft() - 1) : 
			(sheet->GetRowRight() - 1))) * sheet->GetFrameHeight();
	}
	else if (sheet->GetFacingDirection() == Direction::RIGHT)
	{
		tempSrcRect.y = (sheet->GetRowUp() ? (sheet->GetRowUp() - 1) : (sheet->GetRowRight() ? (sheet->GetRowRight() - 1) : 
			(sheet->GetRowLeft() - 1))) * sheet->GetFrameHeight();
	}
	else
	{
		tempSrcRect.y = (sheet->GetRowUp() - 1) * sheet->GetFrameHeight();
		sheet->SetFacingDirection(Direction::UP);
	}	

	sheet->SetSrcRect(tempSrcRect);
}

void Animator::MoveDown(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet)
{
	pos->SetY(pos->GetY() - sheet->GetMovementSpeed()); 
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();

	if (sheet->GetFacingDirection() == Direction::LEFT)
	{
		tempSrcRect.y = (sheet->GetRowDown() ? (sheet->GetRowDown() - 1) : (sheet->GetRowLeft() ? (sheet->GetRowLeft() - 1) : 
			(sheet->GetRowRight() - 1))) * sheet->GetFrameHeight();
	}
	else if (sheet->GetFacingDirection() == Direction::RIGHT)
	{
		tempSrcRect.y = (sheet->GetRowDown() ? (sheet->GetRowDown() - 1) : (sheet->GetRowRight() ? (sheet->GetRowRight() - 1) : 
			(sheet->GetRowLeft() - 1))) * sheet->GetFrameHeight();
	}
	else
	{
		tempSrcRect.y = (sheet->GetRowDown() - 1) * sheet->GetFrameHeight();
		sheet->SetFacingDirection(Direction::DOWN);
	}

	sheet->SetSrcRect(tempSrcRect);
}

void Animator::MoveLeft(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet)
{
	pos->SetX(pos->GetX() - sheet->GetMovementSpeed());
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();
	tempSrcRect.y = (sheet->GetRowLeft() ? (sheet->GetRowLeft() - 1) : (sheet->GetRowRight() - 1)) * sheet->GetFrameHeight();
	sheet->SetFacingDirection(Direction::LEFT);
	sheet->SetSrcRect(tempSrcRect);
}

void Animator::MoveRight(Math::Vector2* pos, std::shared_ptr<SpriteSheet> sheet)
{
	pos->SetX(pos->GetX() + sheet->GetMovementSpeed());
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();
	tempSrcRect.y = (sheet->GetRowRight() ? (sheet->GetRowRight() - 1) : (sheet->GetRowLeft() - 1)) * sheet->GetFrameHeight();
	sheet->SetFacingDirection(Direction::RIGHT);
	sheet->SetSrcRect(tempSrcRect);
}

void Animator::StandIdle(Rendering::UnsignInt32 currentTime, std::shared_ptr<SpriteSheet> sheet)
{
	if (sheet->GetIdleRow() != 0)
	{
		if (currentTime - sheet->GetLastFrameTime() > sheet->GetIdleAnimSpeed())
		{
			sheet->SetIdleCurrentFrame((sheet->GetIdleCurrentFrame() + 1) % sheet->GetIdleFrameCount());

			Rendering::Rect tempSrcRect = sheet->GetSrcRect();
			tempSrcRect.x = sheet->GetIdleCurrentFrame() * sheet->GetFrameWidth();
			sheet->SetSrcRect(tempSrcRect);

			sheet->SetLastFrameTime(currentTime);
		}

		Rendering::Rect tempSrcRect = sheet->GetSrcRect();
		tempSrcRect.y = (sheet->GetIdleRow() - 1) * sheet->GetFrameHeight();
		sheet->SetSrcRect(tempSrcRect);
	}
	else
	{
		sheet->SetCurrentFrame(0);
		Rendering::Rect tempSrcRect = sheet->GetSrcRect();
		tempSrcRect.x = sheet->GetCurrentFrame() * sheet->GetFrameWidth();
		sheet->SetSrcRect(tempSrcRect);
	}
}
