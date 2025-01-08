#include "CollisionSystem.hpp"

Physics::CollisionSystem::CollisionSystem(ecs::View<Collider*> view)
	: ecs::System<Collider*>(view)
{

}

Physics::CollisionSystem::~CollisionSystem()
{
	for (ecs::EntityId entityId : _view)
	{
		delete _view.get<Collider*>(entityId);
	}
}

Physics::Collider* Physics::CollisionSystem::GetCollider(EnginePhysics::PhysicsId id)
{
	for (ecs::EntityId entityId : _view)
	{
		Collider* collider{ _view.get<Collider*>(entityId) };
		if (EnginePhysics::AreEqual(collider->_shape.id, id))
		{
			return collider;
		}
	}

	return nullptr;
}
