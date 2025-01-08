#pragma once

#include <Engine/Delta.hpp>

#include "../Classes/Projectiles/Projectile.hpp"

class DummyBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;
};