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
			: transform{ transform }, _physicsWorld{ world }, _shapeType{ type }
		{
			std::cout << "NewPos: " << transform.position.GetX() << " : " << transform.position.GetY() << std::endl;

			EnginePhysics::PhysicsBody physicsBody = EnginePhysics::DefaultBody();
			physicsBody.position = { transform.position.GetX(), transform.position.GetY() };
			_bodyId = EnginePhysics::CreateBody(_physicsWorld.GetWorldId(), &physicsBody);

			_shape.shape = EnginePhysics::DefaultShape();
			_shape.shape.density = 1.0f;
			switch (_shapeType)
			{
				case Physics::ShapeType::CIRCLE:
					_polygon = EnginePhysics::CreateCircle(transform.scale);
					break;

				case Physics::ShapeType::BOX:
				default:
					_polygon = EnginePhysics::CreateBox(transform.scale);
					break;
			}
			_shape.id = EnginePhysics::CreatePolygonShape(_bodyId, &_shape, &_polygon);
		}

		~Collider()
		{
			EnginePhysics::DestroyCollider(_bodyId, _physicsWorld.GetWorldId());
		}

		friend class CollisionSystem;
		friend class PhysicsSystem;
		friend class Rigidbody;

		void SetTrigger(bool trigger)
		{
			if (_isTrigger == trigger) return;
			_isTrigger = trigger;

			b2DestroyBody(_bodyId);
			EnginePhysics::PhysicsBody physicsBody = EnginePhysics::DefaultBody();
			physicsBody.position = { transform.position.GetX(), transform.position.GetY() };
			_bodyId = EnginePhysics::CreateBody(_physicsWorld.GetWorldId(), &physicsBody);

			_shape.shape = EnginePhysics::DefaultShape();
			_shape.shape.isSensor = _isTrigger;
			_shape.shape.enableContactEvents = _isTrigger;
			_shape.shape.enableSensorEvents = _isTrigger;
			switch (_shapeType)
			{
				case Physics::ShapeType::CIRCLE:
					_polygon = EnginePhysics::CreateCircle(transform.scale);
					break;

				case Physics::ShapeType::BOX:
				default:
					_polygon = EnginePhysics::CreateBox(transform.scale);
					break;
			}
			_shape.id = EnginePhysics::CreatePolygonShape(_bodyId, &_shape, &_polygon);

			CallOnShapeChanged();
		}

		bool IsTrigger() const
		{
			return _isTrigger;
		}

		Transform& transform;
	private:
		EnginePhysics::PhysicsId _bodyId;		   // _b2bodyId
		EnginePhysics::PhysicsPolygon _polygon;		// _b2polygon
		EnginePhysics::PhysicsShape _shape;

		Events::EventDispatcher<const EnginePhysics::PhysicsShape&> _onShapeChanged{};
		bool _isTrigger{ false };

		const Physics::PhysicsWorld& _physicsWorld;
		ShapeType _shapeType;

		void CallOnShapeChanged()
		{
			_onShapeChanged.Dispatch(_shape);
		}
	};
}