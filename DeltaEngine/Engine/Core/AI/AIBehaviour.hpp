#pragma once

#include <vector>
#include <memory>

#include "IAIStrategy.hpp"
#include "../Time.hpp"
#include "../../Transform.hpp"
#include "../../GameObject.hpp"

class AIBehaviour
{
public:
	AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Transform* pos, Transform* targetPos, int range, int step, float speed = 1.0f);
	~AIBehaviour();

	Transform* Update();
    void CalculateNewPath();

	Transform* GetPosition() const;
	void SetPosition(Transform* position);

	Transform* GetTargetPosition() const;
	void SetTargetPosition(Transform* position);

	float GetSpeed() const;
	Math::Vector2 GetDirection() const;

	bool IsWalkable(const Math::Vector2& position);

private:
	const float NEXT_NODE_DISTANCE = 0.3f;

	std::shared_ptr<IAIStrategy> strategy_;
	std::vector<Math::Vector2> path_;

	Transform* position_;
	Transform* _targetPosition;
	Transform _lastKnownTargetPosition;
	bool start{true};

	float _moveSpeed;
	Math::Vector2 _direction;

	int range_;
	int step_;

	bool isWandering = false;
	float wanderCooldown {1.0f};
	float timeSinceLastWander {0.0f};
	Math::Vector2 wanderDirection;

	float pathRecalculationCooldown = 0.5f;	 // Seconds
	float targetChangeThreshold = 1.0f;
};
