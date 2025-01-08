#include "Collider.hpp"

Physics::Collider::Collider(const PhysicsWorld& world, Transform& transform, ShapeType type)
	: transform{ transform }, 
	_physicsWorld{ world }, 
	_shapeType{ type }
{
	_physicsBody = EnginePhysics::DefaultBody();
	_physicsBody.position = { transform.position.GetX(), transform.position.GetY() };
	_bodyId = EnginePhysics::CreateBody(_physicsWorld.GetWorldId(), &_physicsBody);

	_shape.shape = EnginePhysics::DefaultShape();
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

void Physics::Collider::SetTrigger(bool trigger)
{
	if (_isTrigger == trigger)
		return;

	b2DestroyBody(_bodyId);
	_physicsBody = EnginePhysics::DefaultBody();
	_physicsBody.position = { transform.position.GetX(), transform.position.GetY() };
	_bodyId = EnginePhysics::CreateBody(_physicsWorld.GetWorldId(), &_physicsBody);

	_shape.shape = EnginePhysics::DefaultShape();
	_shape.shape.isSensor = trigger;
	_shape.shape.enableContactEvents = trigger;
	_shape.shape.enableSensorEvents = trigger;

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

bool Physics::Collider::IsTrigger() const
{
	return _isTrigger;
}

void Physics::Collider::CallOnShapeChanged()
{
	_onShapeChanged.Dispatch(_shape);
}
