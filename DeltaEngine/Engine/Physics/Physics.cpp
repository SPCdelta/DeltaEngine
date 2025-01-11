#include "Physics.hpp"

EnginePhysics::Event::SensorEventData::SensorEventData(PhysicsShape shape)
	: _shape{shape}
{

}

EnginePhysics::PhysicsShape EnginePhysics::Event::SensorEventData::GetShape() const
{
	return _shape;
}

b2Vec2 EnginePhysics::ToVec2(Math::Vector2 vector)
{
	return b2Vec2
	{
		vector.GetX(), vector.GetY()
	};
}

EnginePhysics::WorldId EnginePhysics::ToWorldId(b2WorldId worldId)
{
	return {worldId.index1, worldId.revision};
}

EnginePhysics::PhysicsId EnginePhysics::ToPhysicsId(b2BodyId bodyId)
{
	return {bodyId.index1, bodyId.world0, bodyId.revision};
}

EnginePhysics::PhysicsId EnginePhysics::ToPhysicsId(b2ShapeId shapeId)
{
	return {shapeId.index1, shapeId.world0, shapeId.revision};
}