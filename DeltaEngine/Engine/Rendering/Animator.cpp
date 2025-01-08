#include "Animator.hpp"

#include "../Core/Time.hpp"

void Animator::Play(std::shared_ptr<AnimationSheet> sheet, Direction direc, bool pauseWalk)
{
	bool isMoving = true;
	Rendering::UnsignInt32 currentTime = static_cast<Rendering::UnsignInt32>(Rendering::GetTicks() * Time::GetMultiplier());	
	if (!pauseWalk && currentTime - sheet->GetLastMoveTime() >= sheet->GetMoveInterval())
	{
		if (direc == Direction::UP)			// up 
			MoveUp(sheet);
		else if (direc == Direction::LEFT)  // left
			MoveLeft(sheet);
		else if (direc == Direction::DOWN)  // down
			MoveDown(sheet);
		else if (direc == Direction::RIGHT) // right
			MoveRight(sheet);
		else
			isMoving = false;

		if (isMoving && currentTime - sheet->GetLastFrameTime() > static_cast<Rendering::UnsignInt32>(sheet->GetAnimationSpeed()))
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
}

void Animator::MoveUp(std::shared_ptr<AnimationSheet> sheet)
{
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();

	if (sheet->GetRowUp() == 0 && sheet->GetFacingDirection() == Direction::LEFT)
	{
		tempSrcRect.y = (sheet->GetRowUp() ? (sheet->GetRowUp() - 1) : (sheet->GetRowLeft() ? (sheet->GetRowLeft() - 1) : 
			(sheet->GetRowRight() - 1))) * sheet->GetFrameHeight();
	}
	else if (sheet->GetRowUp() == 0 && sheet->GetFacingDirection() == Direction::RIGHT)
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

void Animator::MoveDown(std::shared_ptr<AnimationSheet> sheet)
{
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();

	if (sheet->GetRowDown() == 0 && sheet->GetFacingDirection() == Direction::LEFT)
	{
		tempSrcRect.y = (sheet->GetRowDown() ? (sheet->GetRowDown() - 1) : (sheet->GetRowLeft() ? (sheet->GetRowLeft() - 1) : 
			(sheet->GetRowRight() - 1))) * sheet->GetFrameHeight();
	}
	else if (sheet->GetRowDown() == 0 && sheet->GetFacingDirection() == Direction::RIGHT)
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

void Animator::MoveLeft(std::shared_ptr<AnimationSheet> sheet)
{
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();
	tempSrcRect.y = (sheet->GetRowLeft() ? (sheet->GetRowLeft() - 1) : (sheet->GetRowRight() - 1)) * sheet->GetFrameHeight();
	sheet->SetFacingDirection(Direction::LEFT);
	sheet->SetSrcRect(tempSrcRect);
}

void Animator::MoveRight(std::shared_ptr<AnimationSheet> sheet)
{
	Rendering::Rect tempSrcRect = sheet->GetSrcRect();
	tempSrcRect.y = (sheet->GetRowRight() ? (sheet->GetRowRight() - 1) : (sheet->GetRowLeft() - 1)) * sheet->GetFrameHeight();
	sheet->SetFacingDirection(Direction::RIGHT);
	sheet->SetSrcRect(tempSrcRect);
}

void Animator::StandIdle(Rendering::UnsignInt32 currentTime, std::shared_ptr<AnimationSheet> sheet)
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
