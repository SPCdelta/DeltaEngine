#pragma once

#include "Physics.hpp"

namespace Physics
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld()
		{
			_data.world = b2DefaultWorldDef();
			_data.id = Physics::Facade::ToWorldId(b2CreateWorld(&_data.world));
		}

		~PhysicsWorld()
		{
			b2DestroyWorld(static_cast<b2WorldId>(_data.id));
		}

		const WorldId& GetWorldId() const
		{
			return _data.id;
		}

	private:
		WorldData _data;
	};
}