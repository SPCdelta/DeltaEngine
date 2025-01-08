#include "PhysicsWorld.hpp"

Physics::PhysicsWorld::PhysicsWorld()
{
	_data = EnginePhysics::CreateWorld();
}

Physics::PhysicsWorld::~PhysicsWorld()
{
	EnginePhysics::DestroyWorld(_data.id);
}

const EnginePhysics::WorldId& Physics::PhysicsWorld::GetWorldId() const
{
	return _data.id;
}

void Physics::PhysicsWorld::Update()
{
	_currentCollisions.clear();
	_currentTriggers.clear();

	EnginePhysics::AdvancePhysics(_data.id, Time::GetDeltaTime(), EnginePhysics::SUB_STEP_COUNT);

	EnginePhysics::CollisionEvents contactEvents = EnginePhysics::GetCollisionEvents(_data.id);
	EnginePhysics::TriggerEvents triggerEvents = EnginePhysics::GetTriggerEvents(_data.id);

	// # Collision Event
	// Enters
	for (int i = 0; i < contactEvents.beginCount; ++i)
	{
		EnginePhysics::CollisionTouchStartEvent* touch = contactEvents.beginEvents + i;
		_currentCollisions.push_back(
			{
				EnginePhysics::ToPhysicsId(touch->shapeIdA),
				EnginePhysics::ToPhysicsId(touch->shapeIdB),
				CollisionState::ENTER
			}
		);
	}

	// Exits
	for (int i = 0; i < contactEvents.endCount; ++i)
	{
		EnginePhysics::CollisionTouchEndEvent* touch = contactEvents.endEvents + i;
		_currentTriggers.push_back(
			{ 
				EnginePhysics::ToPhysicsId(touch->shapeIdA),
				EnginePhysics::ToPhysicsId(touch->shapeIdB),
				CollisionState::EXIT
			}
		);
	}

	// # Trigger Events
	// Enters
	for (int i = 0; i < triggerEvents.beginCount; ++i)
	{
		EnginePhysics::TriggerTouchStartEvent* touch = triggerEvents.beginEvents + i;
		_currentTriggers.push_back(
			{
				EnginePhysics::ToPhysicsId(touch->visitorShapeId),
				EnginePhysics::ToPhysicsId(touch->sensorShapeId),
				CollisionState::ENTER
			}
		);
	}

	// Exits
	for (int i = 0; i < triggerEvents.endCount; ++i)
	{
		EnginePhysics::TriggerTouchEndEvent* touch = triggerEvents.endEvents + i;
		_currentTriggers.push_back(
			{ 
				EnginePhysics::ToPhysicsId(touch->visitorShapeId), 
				EnginePhysics::ToPhysicsId(touch->sensorShapeId),
				CollisionState::EXIT
			}
		);
	}
}

std::vector<Physics::CollisionData>& Physics::PhysicsWorld::GetCurrentTriggers()
{
	return _currentTriggers;
}

const std::vector<Physics::CollisionData>& Physics::PhysicsWorld::GetCurrentTriggers() const
{
	return _currentTriggers;
}

std::vector<Physics::CollisionData>& Physics::PhysicsWorld::GetCurrentCollisions()
{
	return _currentCollisions;
}

const std::vector<Physics::CollisionData>& Physics::PhysicsWorld::GetCurrentCollisions() const
{
	return _currentCollisions;
}
