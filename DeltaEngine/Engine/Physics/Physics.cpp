#include "Physics.hpp"

EnginePhysics::Event::SensorEventData::SensorEventData(PhysicsShape shape)
	: _shape{shape}
{

}

EnginePhysics::PhysicsShape EnginePhysics::Event::SensorEventData::GetShape() const
{
	return _shape;
}