#include "AIBehaviour.hpp"

AIBehaviour::AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Math::Vector2* pos, Math::Vector2* targetPos, int range, int step, float speed = 1.0f) : 
		strategy_(strategy), position_(pos), _targetPosition(targetPos), _moveSpeed(speed), range_(range), step_(step) {}

AIBehaviour::~AIBehaviour()
{
	position_ = nullptr;
	_targetPosition = nullptr;
}

Math::Vector2* AIBehaviour::Update()
{
	if (!_targetPosition || range_ <= 0 || step_ <= 0)
	{
		_direction = {0.0f, 0.0f};
		return position_;
	}

	Math::Vector2 distanceToPlayer = *_targetPosition - *position_;
	if (distanceToPlayer.Magnitude() > range_) 
	{
		// Player is out of range, start wandering
		isWandering = true;
		timeSinceLastWander += Time::GetDeltaTime();

		// If enough time has passed, change the wandering direction
		if (timeSinceLastWander > wanderCooldown)
		{
			wanderDirection = Math::Vector2(rand() % 3 - 1, rand() % 3 - 1); 
			wanderDirection = wanderDirection.GetNormalized(); 
			timeSinceLastWander = 0.0f;
		}

		_direction = wanderDirection;
		*position_ += _direction * _moveSpeed * Time::GetDeltaTime();
		return position_;
	}

	 isWandering = false;
		 
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
		return position_;

	_direction = path_.front() - *position_;
	float distance = _direction.Magnitude();

    if (distance < 0.3f)  // Reached the next 'node'
    {
		if (path_.size() == 1 && path_.front() == *_targetPosition)
		{
			path_.clear();
			return position_;
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

	return position_;
}

void AIBehaviour::CalculateNewPath()
{
	if (strategy_) 
	{
		auto newPath = strategy_->CalculatePath(*position_, *_targetPosition, range_, step_);
		if (!newPath.empty() && ((*_targetPosition - newPath.front()).Magnitude() < (*_targetPosition - *position_).Magnitude())) 
			path_ = std::move(newPath);
	}
}

Math::Vector2* AIBehaviour::GetPosition() const
{
	return position_;
}

void AIBehaviour::SetPosition(Math::Vector2* position)
{
	position_ = position;
}

Math::Vector2* AIBehaviour::GetTargetPosition() const
{
	return _targetPosition;
}

void AIBehaviour::SetTargetPosition(Math::Vector2* position)
{
	_targetPosition = position;
}

Math::Vector2 AIBehaviour::GetDirection()
{
	return _direction;
}