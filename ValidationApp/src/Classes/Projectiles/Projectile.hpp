#pragma once

#include <Engine/Delta.hpp>

struct ProjectileData
{
	std::string sprite;
	int damage;
	float speed;
	Math::Vector2 direction;
};

constexpr float DEFAULT_LIFETIME = 2.0f;

class Projectile : public BehaviourScript
{
public:
	~Projectile();

	void OnStart() override;
	void OnUpdate() override;

	const ProjectileData& GetProjectileData() const;
	void SetProjectileData(ProjectileData data);

	Rigidbody* rigidbody = nullptr;

private:
	ProjectileData _data{};
};