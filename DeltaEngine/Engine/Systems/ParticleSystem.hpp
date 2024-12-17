#pragma once

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"

#include "../Rendering/Particles/ParticleEmitter.hpp"

class ParticleSystem : public ecs::System<Transform, ParticleEmitter>
{
public:
	ParticleSystem(ecs::View<Transform, ParticleEmitter> view)
		: ecs::System<Transform, ParticleEmitter>(view)
	{

	}

	void Update()
	{
		for (ecs::EntityId entityId : _view)
		{
			ParticleEmitter& emitter = _view.get<ParticleEmitter>(entityId);
			emitter.Update();
		}
	}
};