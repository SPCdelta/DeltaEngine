#include "PhysicsWorld.hpp"

void Physics::PhysicsWorld::Update()
{
	_currentCollisions.clear();
	_currentTriggers.clear();

	b2World_Step(_data.id, Physics::TIME_STEP, Physics::SUB_STEP_COUNT);

	b2SensorEvents sensorEvents = b2World_GetSensorEvents(_data.id);
	b2ContactEvents contactEvents = b2World_GetContactEvents(_data.id);

	// # Collision Event
	// Enters
	for (int i = 0; i < contactEvents.beginCount; ++i)
	{
		b2ContactBeginTouchEvent* touch = contactEvents.beginEvents + i;
		_currentCollisions.push_back(
			{
				Physics::Facade::ToPhysicsId(touch->shapeIdA),
				Physics::Facade::ToPhysicsId(touch->shapeIdB),
				CollisionState::ENTER
			}
		);
	}

	// Exits
	for (int i = 0; i < contactEvents.endCount; ++i)
	{
		b2ContactEndTouchEvent* touch = contactEvents.endEvents + i;
		_currentTriggers.push_back(
			{ 
				Physics::Facade::ToPhysicsId(touch->shapeIdA),
				Physics::Facade::ToPhysicsId(touch->shapeIdB),
				CollisionState::EXIT
			}
		);
	}

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
