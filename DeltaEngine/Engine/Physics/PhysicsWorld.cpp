#include "PhysicsWorld.hpp"

void Physics::PhysicsWorld::Update()
{
	_currentCollisions.clear();
	_currentTriggers.clear();

	Physics::AdvancePhysics(_data.id, Physics::TIME_STEP, Physics::SUB_STEP_COUNT);

	CollisionEvents contactEvents = Physics::GetCollisionEvents(_data.id);
	TriggerEvents triggerEvents = Physics::GetTriggerEvents(_data.id);

	// # Collision Event
	// Enters
	for (int i = 0; i < contactEvents.beginCount; ++i)
	{
		CollisionTouchStartEvent* touch = contactEvents.beginEvents + i;
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
		CollisionTouchEndEvent* touch = contactEvents.endEvents + i;
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
	for (int i = 0; i < triggerEvents.beginCount; ++i)
	{
		TriggerTouchStartEvent* touch = triggerEvents.beginEvents + i;
		_currentTriggers.push_back(
			{
				Physics::Facade::ToPhysicsId(touch->visitorShapeId),
				Physics::Facade::ToPhysicsId(touch->sensorShapeId),
				CollisionState::ENTER
			}
		);
	}

	// Exits
	for (int i = 0; i < triggerEvents.endCount; ++i)
	{
		TriggerTouchEndEvent* touch = triggerEvents.endEvents + i;
		_currentTriggers.push_back(
			{ 
				Physics::Facade::ToPhysicsId(touch->visitorShapeId), 
				Physics::Facade::ToPhysicsId(touch->sensorShapeId),
				CollisionState::EXIT
			}
		);
	}
}
