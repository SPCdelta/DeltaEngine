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

	class Collider
	{
	public:
		Collider(const PhysicsWorld& world, const Transform& transform, ShapeType type)
		{
			_physicsBody = b2DefaultBodyDef();
			_physicsBody.position = { transform.position.x, transform.position.y };
			_bodyId = Physics::Facade::ToPhysicsId(b2CreateBody(world.GetWorldId(), &_physicsBody));

			_shape.shape = b2DefaultShapeDef();
			switch (type)
			{
			case Physics::ShapeType::CIRCLE:
				_polygon = b2MakeBox(transform.scale.x / 2.0f, transform.scale.y / 2.0f);
				break;

			case Physics::ShapeType::BOX:
			default:
				_polygon = b2MakeBox(transform.scale.x / 2.0f, transform.scale.y / 2.0f);
				break;
			}
			_shape.id = Physics::Facade::ToPhysicsId(b2CreatePolygonShape(_bodyId, &_shape.shape, &_polygon));
		}

		friend class Rigidbody;

		void SetTrigger(bool trigger)
		{
			if (_isTrigger == trigger) return;

			b2DestroyShape(_shape.id);
			_shape.shape.isSensor = trigger;
			_shape.shape.enableSensorEvents = trigger;
			_shape.id = Physics::Facade::ToPhysicsId(b2CreatePolygonShape(_bodyId, &_shape.shape, &_polygon));
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

		void CallOnShapeChanged()
		{
			_onShapeChanged.Dispatch(_shape);
		}
	};
}