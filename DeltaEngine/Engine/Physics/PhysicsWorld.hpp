#pragma once

#include <vector>

#include "Physics.hpp"
#include "../Ecs/Registry.hpp"

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
		PhysicsId rbShapeId;
		PhysicsId colliderShapeId;
		CollisionState state;
	};

	class PhysicsWorld
	{
	public:
		PhysicsWorld()
		{
			_data.world = b2DefaultWorldDef();
			_data.id = Physics::Facade::ToWorldId(b2CreateWorld(&_data.world));
		}

		~PhysicsWorld() { Physics::DestroyWorld(_data.id); }

		friend class Rigidbody;

		const WorldId& GetWorldId() const { return _data.id; }

		void Update();

		std::vector<CollisionData>& GetCurrentTriggers() { return _currentTriggers; }
		const std::vector<CollisionData>& GetCurrentTriggers() const { return _currentTriggers; }
		
		std::vector<CollisionData>& GetCurrentCollisions() { return _currentCollisions; }
		const std::vector<CollisionData>& GetCurrentCollisions() const{ return _currentCollisions; }

	private:
		WorldData _data;

		std::vector<CollisionData> _currentTriggers;
		std::vector<CollisionData> _currentCollisions;
	};
}