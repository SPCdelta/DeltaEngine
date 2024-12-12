#pragma once

#include <vector>

#include "../Math/Point.hpp"
#include "IAIStrategy.hpp"

class AIBehaviour
{
   public:
	AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Math::Vector2* pos, Math::Vector2* targetPos, float speed = 1.0f) : 
		strategy_(strategy), position_(pos), _targetPosition(targetPos), _moveSpeed(speed) {}

	~AIBehaviour()
	{
		position_ = nullptr;
		_targetPosition = nullptr;
	}

	void Update()
	{
		if (!_targetPosition)
			return;

		float pathRecalculationCooldown = 1.0f;	 // Seconds
		static float timeSinceLastPathCalculation = 0.0f;
		timeSinceLastPathCalculation += Time::GetDeltaTime();

		float targetChangeThreshold = 2.0f; 

		if (start || ((*_targetPosition - _lastKnownTargetPosition).Magnitude() > targetChangeThreshold && 
			timeSinceLastPathCalculation > pathRecalculationCooldown)) 
		{
            _lastKnownTargetPosition = *_targetPosition;
			CalculateNewPath();
			timeSinceLastPathCalculation = 0.0f;
			start = false;
        }
		else
		{
			_direction = {0.0f, 0.0f};
		}

		if (path_.empty())
			return;

		_direction = path_.front() - *position_;
		float distance = _direction.Magnitude();

        if (distance < 0.3f)  // Reached the next 'node'
        {
			if (path_.size() == 1 && path_.front() == *_targetPosition)
			{
				path_.clear();
				return;
			}

            *position_ = path_.front();
            path_.erase(path_.begin());
        }
        else
        {
			Math::Vector2 normalizedDirection = _direction.GetNormalized();
			*position_ += normalizedDirection * _moveSpeed * Time::GetDeltaTime();
			_direction = normalizedDirection;
        }
	}

    void CalculateNewPath()
	{
		if (strategy_) 
		{
			auto newPath = strategy_->CalculatePath(*position_, *_targetPosition);
			if (!newPath.empty() && ((*_targetPosition - newPath.front()).Magnitude() < (*_targetPosition - *position_).Magnitude())) 
				path_ = std::move(newPath);
		}
	}

	Math::Vector2* GetPosition() const { return position_; }
	void SetPosition(Math::Vector2* position) { position_ = position; }

	Math::Vector2* GetTargetPosition() const { return _targetPosition; }
	void SetTargetPosition(Math::Vector2* position) { _targetPosition = position; }

	Math::Vector2 GetDirection() { return _direction; }

   private:
	std::shared_ptr<IAIStrategy> strategy_;
	std::vector<Math::Vector2> path_;

	Math::Vector2* position_;
	Math::Vector2* _targetPosition;
	Math::Vector2 _lastKnownTargetPosition;
	bool start{true};

	float _moveSpeed;
	Math::Vector2 _direction;
};
