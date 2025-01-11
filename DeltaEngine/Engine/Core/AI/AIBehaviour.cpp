#include "AIBehaviour.hpp"

AIBehaviour::AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Transform* pos, Transform* targetPos, int range, int step, float speed) 
	: strategy_(strategy), 
	  position_(pos), 
	  _targetPosition(targetPos), 
	  _moveSpeed(speed), 
	  range_(range), 
	  step_(step) 
{

}

AIBehaviour::~AIBehaviour()
{
	position_ = nullptr;
	_targetPosition = nullptr;
}

Transform* AIBehaviour::Update()
{
	if (!_targetPosition || range_ <= 0 || step_ <= 0)
	{
		_direction = {0.0f, 0.0f};
		return position_;
	}

	Math::Vector2 distanceToPlayer = _targetPosition->position - position_->position;
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

		Math::Vector2 targetPos = position_->position + wanderDirection * _moveSpeed * Time::GetDeltaTime();
		if (IsWalkable(targetPos))
		{
			_direction = wanderDirection;
			position_->position += _direction * _moveSpeed * Time::GetDeltaTime();		
		}
		return position_;		
	}

	isWandering = false;
		 	
	static float timeSinceLastPathCalculation = 0.0f;
	timeSinceLastPathCalculation += Time::GetDeltaTime();

	if (start || ((_targetPosition->position - _lastKnownTargetPosition.position).Magnitude() > targetChangeThreshold && 
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
		return position_; // No path to follow

	_direction = path_.front() - position_->position;
	float distance = _direction.Magnitude();

    if (distance < NEXT_NODE_DISTANCE)	// Reached the next 'node'
    {
		if (path_.size() == 1 && path_.front() == _targetPosition->position)
		{
			path_.clear();
			return position_;
		}

        position_->position = path_.front();
        path_.erase(path_.begin());
    }
    else
    {
		Math::Vector2 normalizedDirection = _direction.GetNormalized();
		position_->position += normalizedDirection * _moveSpeed * Time::GetDeltaTime();
		_direction = normalizedDirection;
    }

	return position_;
}

void AIBehaviour::CalculateNewPath()
{
	if (strategy_) 
	{
		auto newPath = strategy_->CalculatePath(position_, _targetPosition->position, range_, step_);
		if (!newPath.empty() && ((_targetPosition->position - newPath.front()).Magnitude() < (_targetPosition->position - position_->position).Magnitude())) 
			path_ = std::move(newPath);
	}
}

Transform* AIBehaviour::GetPosition() const
{
	return position_;
}

void AIBehaviour::SetPosition(Transform* position)
{
	position_ = position;
}

Transform* AIBehaviour::GetTargetPosition() const
{
	return _targetPosition;
}

void AIBehaviour::SetTargetPosition(Transform* position)
{
	_targetPosition = position;
}

float AIBehaviour::GetSpeed() const
{
	return _moveSpeed;
}

Math::Vector2 AIBehaviour::GetDirection() const
{
	return _direction;
}

bool AIBehaviour::IsWalkable(const Math::Vector2& position)
{
	return strategy_->IsWalkable(position);
}