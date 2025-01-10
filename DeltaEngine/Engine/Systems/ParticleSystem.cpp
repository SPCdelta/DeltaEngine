#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(ecs::Registry& reg)
	: ecs::System<Transform, ParticleEmitter>(reg)
{

}

void ParticleSystem::Update()
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		ParticleEmitter& emitter = _view.get<ParticleEmitter>(entityId);
		emitter.Update();
	}
}