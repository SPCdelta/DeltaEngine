#pragma once

#include "PhysicsWorld.hpp"

namespace Physics
{
	enum class ShapeType
	{
		BOX = 0,
		CIRCLE = 1
	};

	class Rigidbody;
	class CollisionSystem;
	class PhysicsSystem;

	class Collider
	{
	public:
		Collider(const PhysicsWorld& world, Transform& transform, ShapeType type);

		friend class CollisionSystem;
		friend class PhysicsSystem;
		friend class Rigidbody;

		void SetTrigger(bool trigger);
		bool IsTrigger() const;

		EnginePhysics::PhysicsId GetId();

		Transform& transform;

	private:
		EnginePhysics::PhysicsId _bodyId;			// _b2bodyId
		EnginePhysics::PhysicsPolygon _polygon;		// _b2polygon
		EnginePhysics::PhysicsShape _shape;

		Events::EventDispatcher<const EnginePhysics::PhysicsShape&> _onShapeChanged{};
		bool _isTrigger{false};

		const Physics::PhysicsWorld& _physicsWorld;
		ShapeType _shapeType;

		void CallOnShapeChanged();
	};
}