#pragma once

#include "../Ecs/Include.hpp"
#include "../Transform.hpp"

#include "../Rendering/Particles/ParticleEmitter.hpp"

class ParticleSystem : public ecs::System<Transform, ParticleEmitter>
{
public:
	ParticleSystem(ecs::Registry& reg)
		: ecs::System<Transform, ParticleEmitter>(reg)
	{

	}

	void Update()
	{
		RefreshView();
		for (ecs::EntityId entityId : _view)
		{
			ParticleEmitter& emitter = _view.get<ParticleEmitter>(entityId);
			emitter.Update();
		}
	}
};