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

	struct TestData
	{
		PhysicsId rbShapeId;
		PhysicsId colliderShapeId;
		CollisionState state;
	};

	class PhysicsWorld
	{
	public:
		PhysicsWorld(ecs::Registry& reg)
			: _reg{ reg }
		{
			_data.world = b2DefaultWorldDef();
			_data.id = Physics::Facade::ToWorldId(b2CreateWorld(&_data.world));
		}

		~PhysicsWorld()
		{
			b2DestroyWorld(static_cast<b2WorldId>(_data.id));
		}

		friend class Rigidbody;

		const WorldId& GetWorldId() const
		{
			return _data.id;
		}

		void Update()
		{
			//_sensorEvents.clear();
			//_collisionEvents.clear();
			_currentTriggers.clear();

			b2SensorEvents sensorEvents = b2World_GetSensorEvents(_data.id);
			//b2ContactEvents contactEvents = b2World_GetContactEvents(_data.id);

			// # Collision Event
			// Exits


			// Enters
			

			// # Trigger Events
			// Enters
			for (int i = 0; i < sensorEvents.beginCount; ++i)
			{
				b2SensorBeginTouchEvent* touch = sensorEvents.beginEvents + i;
				_currentTriggers.push_back(
					{
						Physics::Facade::ToPhysicsId(touch->visitorShapeId),
						Physics::Facade::ToPhysicsId(touch->sensorShapeId),
						CollisionState::ENTER
					}
				);
			}

			// Exits
			for (int i = 0; i < sensorEvents.endCount; ++i)
			{
				b2SensorEndTouchEvent* touch = sensorEvents.endEvents + i;
				_currentTriggers.push_back(
					{ 
						Physics::Facade::ToPhysicsId(touch->visitorShapeId), 
						Physics::Facade::ToPhysicsId(touch->sensorShapeId),
						CollisionState::EXIT
					}
				);
			}
		}

		std::vector<TestData>& GetCurrentTriggers()
		{
			return _currentTriggers;
		}

		const std::vector<TestData>& GetCurrentTriggers() const
		{
			return _currentTriggers;
		}

	private:
		WorldData _data;
		ecs::Registry& _reg;

		std::vector<TestData> _currentTriggers;
	};
}