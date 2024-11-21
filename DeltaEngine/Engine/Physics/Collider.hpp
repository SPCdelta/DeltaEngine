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
		Collider(const PhysicsWorld& world, Transform& transform, ShapeType type)
			: _transform{ transform }
		{
			_physicsBody = Physics::DefaultBody();
			_physicsBody.position = { transform.position.GetX(), transform.position.GetY() };
			_bodyId = Physics::CreateBody(world.GetWorldId(), &_physicsBody);

			_shape.shape = Physics::DefaultShape();
			switch (type)
			{
				case Physics::ShapeType::CIRCLE:
					_polygon = Physics::CreateCircle(transform.scale);
					break;

				case Physics::ShapeType::BOX:
				default:
					_polygon = Physics::CreateBox(transform.scale);
					break;
			}
			_shape.id = Physics::CreatePolygonShape(_bodyId, &_shape, &_polygon);
		}

		friend class CollisionSystem;
		friend class PhysicsSystem;
		friend class Rigidbody;

		void SetTrigger(bool trigger)
		{
			if (_isTrigger == trigger) return;

			Physics::DestroyShape(_shape.id);
			_shape.shape.isSensor = trigger;
			_shape.shape.enableSensorEvents = trigger;
			_shape.id = Physics::CreatePolygonShape(_bodyId, &_shape, &_polygon);
			_isTrigger = trigger;

			CallOnShapeChanged();
		}

		bool IsTrigger() const
		{
			return _isTrigger;
		}

	private:
		PhysicsBody _physicsBody; // _b2bodyDef
		PhysicsId _bodyId; // _b2bodyId
		PhysicsPolygon _polygon; // _b2polygon
		PhysicsShape _shape;
		Events::EventDispatcher<const PhysicsShape&> _onShapeChanged{};
		bool _isTrigger{ false };
		Transform& _transform;

		void CallOnShapeChanged()
		{
			_onShapeChanged.Dispatch(_shape);
		}
	};
}