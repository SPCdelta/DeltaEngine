#pragma once

#include "Physics.hpp"

namespace Physics
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld()
		{
			_worldDef = b2DefaultWorldDef();
			_worldId = b2CreateWorld(&_worldDef);
		}

		~PhysicsWorld()
		{
			b2DestroyWorld(_worldId);
		}

	private:
		b2WorldDef _worldDef;
		b2WorldId _worldId;
	};
}