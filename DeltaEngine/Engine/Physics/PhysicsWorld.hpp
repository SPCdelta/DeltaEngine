#pragma once

#include <vector>

#include "Physics.hpp"
#include "../Ecs/Registry.hpp"
#include <iostream>

namespace Physics
{
	class Rigidbody;

	enum class CollisionState
	{
		ENTER = 0,
		EXIT = 1
	};

	struct CollisionData
	{
		EnginePhysics::PhysicsId shape1;
		EnginePhysics::PhysicsId shape2;
		CollisionState state;
	};

	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		friend class Rigidbody;

		const EnginePhysics::WorldId& GetWorldId() const;

		void Update();

		std::vector<CollisionData>& GetCurrentTriggers();
		const std::vector<CollisionData>& GetCurrentTriggers() const;
		
		std::vector<CollisionData>& GetCurrentCollisions();
		const std::vector<CollisionData>& GetCurrentCollisions() const;

	private:
		EnginePhysics::WorldData _data;

		std::vector<CollisionData> _currentTriggers;
		std::vector<CollisionData> _currentCollisions;
	};
}