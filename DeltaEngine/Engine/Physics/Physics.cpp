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