#include "Collider.hpp"

Physics::Collider::Collider(const PhysicsWorld& world, Transform& transform, ShapeType type)
	: transform{ transform }, 
	_physicsWorld{ world }, 
	_shapeType{ type }
{
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

void Physics::Collider::SetTrigger(bool trigger)
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

bool Physics::Collider::IsTrigger() const
{
	return _isTrigger;
}

void Physics::Collider::CallOnShapeChanged()
{
	_onShapeChanged.Dispatch(_shape);
}

EnginePhysics::PhysicsId Physics::Collider::GetId() const
{
	return _bodyId;
}
