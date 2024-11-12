#pragma once

#include "Physics.hpp"

namespace Physics
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld()
		{
			_data.world = b2DefaultWorldDef();
			_data.id = Physics::Facade::ToWorldId(b2CreateWorld(&_data.world));
		}

		~PhysicsWorld()
		{
			b2DestroyWorld(static_cast<b2WorldId>(_data.id));
		}

		const WorldId& GetWorldId() const
		{
			return _data.id;
		}

		void Update()
		{
			b2SensorEvents sensorEvents = b2World_GetSensorEvents(_data.id);

			// # Collision Event
			// Exits


			// Enters
			

			// # Trigger Events
			// Exits
			for (int i = 0; i < sensorEvents.endCount; ++i)
			{
				b2SensorEndTouchEvent* touch = sensorEvents.endEvents + i;
				// TODO: call on Collider => OnTriggerExit
			}

			// Enters
			for (int i = 0; i < sensorEvents.beginCount; ++i)
			{
				b2SensorBeginTouchEvent* touch = sensorEvents.beginEvents + i;
				// TODO: call on Collider => OnTriggerEnter
			}
		}

	private:
		WorldData _data;
	};
}