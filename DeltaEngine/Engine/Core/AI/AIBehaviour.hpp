#pragma once

#include <vector>

#include "../Math/Point.hpp"
#include "IAIStrategy.hpp"

class AIBehaviour
{
   public:
	AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Math::Vector2* pos, Math::Vector2* targetPos, float speed = 1.0f) : 
		strategy_(strategy), position_(pos), _targetPosition(targetPos), _moveSpeed(speed) {}

	void Update()
	{
		if (!_targetPosition)
			return;

		/*static float timeSinceLastPathCalculation = 0.0f;
		timeSinceLastPathCalculation += Time::GetDeltaTime();*/
		float targetChangeThreshold = 1.0f; 

        // Check if the target's position has changed
        if ((*_targetPosition - lastKnownTargetPosition_).Magnitude() > targetChangeThreshold /*|| (*_targetPosition - *position_).Magnitude() < 0.5f*/) 
		{
            lastKnownTargetPosition_ = *_targetPosition;
            std::cout << "Target position changed!" << std::endl;

			CalculateNewPath();
			//timeSinceLastPathCalculation = 0.0f;
        }

		if (path_.empty())
			return;

        Math::Vector2 direction = path_.front() - *position_;
        float distance = direction.Magnitude();

        if (distance < 0.1f)  // Reached the next node.
        {
			if (path_.size() == 1 && path_.front() == *_targetPosition)
			{
				path_.clear();	// Stop as the final target has been reached
				return;
			}

            *position_ = path_.front();
            path_.erase(path_.begin());
        }
        else
        {
            Math::Vector2 normalizedDirection = direction.GetNormalized();
			*position_ += normalizedDirection * _moveSpeed * Time::GetDeltaTime();  // Smooth movement

        }
	}

    void CalculateNewPath()
	{
		if (strategy_)
			path_ = strategy_->CalculatePath(*position_, *_targetPosition);
	}

	Math::Vector2* GetPosition() const { return position_; }
	void SetPosition(Math::Vector2* position) { position_ = position; }

	Math::Vector2* GetTargetPosition() const { return _targetPosition; }
	void SetTargetPosition(Math::Vector2* position) { _targetPosition = position; }

   private:
	std::shared_ptr<IAIStrategy> strategy_;
	std::vector<Math::Vector2> path_;

	Math::Vector2* position_;
	Math::Vector2* _targetPosition;
	Math::Vector2 lastKnownTargetPosition_;

	float _moveSpeed;
};
