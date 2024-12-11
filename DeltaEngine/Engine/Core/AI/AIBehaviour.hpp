#pragma once

#include <vector>

#include "../Math/Point.hpp"
#include "IAIStrategy.hpp"

class AIBehaviour
{
   public:
	AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Math::Vector2* pos, Math::Vector2* targetPos) : strategy_(strategy), position_(pos), _targetPosition(targetPos) {}

	void Update()
	{
		//if (!position_ || !_targetPosition)
		//	return;

		//path_ = strategy_->CalculatePath(*position_, *_targetPosition);

		//if (!path_.empty())
		//{
		//	// Move to the next point in the path
		//	position_ = &path_.front();
		//	path_.erase(path_.begin());
		//}
	}

	Math::Vector2* GetPosition() const { return position_; }
	void SetPosition(Math::Vector2* position) { position_ = position; }
	//void SetPlayerPosition(Math::Vector2* position) { _targetPosition = position; }

   private:
	std::shared_ptr<IAIStrategy> strategy_;
	std::vector<Math::Vector2> path_;

	Math::Vector2* position_;
	Math::Vector2* _targetPosition;
};
