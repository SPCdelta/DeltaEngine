#include "CollisionSystem.hpp"

Physics::CollisionSystem::CollisionSystem(ecs::Registry& reg)
	: ecs::System<std::unique_ptr<Collider>>(reg)
{

}

Physics::Collider* Physics::CollisionSystem::GetCollider(EnginePhysics::PhysicsId id)
{
	RefreshView();

	for (ecs::EntityId entityId : _view)
	{
		std::unique_ptr<Collider>& collider = _view.get<std::unique_ptr<Collider>>(entityId);
		if (EnginePhysics::AreEqual(collider->_shape.id, id))
			return collider.get();
	}

	return nullptr;
}
