#pragma once

#include <vector>
#include <memory>

#include "IAIStrategy.hpp"
#include "../Time.hpp"

class AIBehaviour
{
   public:
	AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Math::Vector2* pos, Math::Vector2* targetPos, int range, int step, float speed);
	~AIBehaviour();

	Math::Vector2* Update();
    void CalculateNewPath();

	Math::Vector2* GetPosition() const;
	void SetPosition(Math::Vector2* position);

	Math::Vector2* GetTargetPosition() const;
	void SetTargetPosition(Math::Vector2* position);

	float GetSpeed();
	Math::Vector2 GetDirection();

   private:
	std::shared_ptr<IAIStrategy> strategy_;
	std::vector<Math::Vector2> path_;

	Math::Vector2* position_;
	Math::Vector2* _targetPosition;
	Math::Vector2 _lastKnownTargetPosition;
	bool start{true};

	float _moveSpeed;
	Math::Vector2 _direction;

	int range_;
	int step_;

	bool isWandering = false;
	float wanderCooldown {1.0f};
	float timeSinceLastWander {0.0f};
	Math::Vector2 wanderDirection;
};