#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(ecs::View<Transform, ParticleEmitter> view)
	: ecs::System<Transform, ParticleEmitter>(view)
{

}

void ParticleSystem::Update()
{
	for (ecs::EntityId entityId : _view)
	{
		ParticleEmitter& emitter = _view.get<ParticleEmitter>(entityId);
		emitter.Update();
	}
}