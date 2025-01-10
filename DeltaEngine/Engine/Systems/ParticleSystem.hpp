#pragma once

#include "../Ecs/Include.hpp"
#include "../Transform.hpp"
#include "../Rendering/Particles/ParticleEmitter.hpp"

class ParticleSystem : public ecs::System<Transform, ParticleEmitter>
{
public:
	ParticleSystem(ecs::Registry& reg);

	void Update();
};