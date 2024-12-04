#pragma once

#include <Engine/Delta.hpp>

struct ProjectileData
{
	std::string sprite;
	int damage;
	float speed;
	Math::Vector2 direction;
};

constexpr float DEFAULT_PROJECTILE_DESPAWN_TIME = 30.0f;

class Projectile : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	void SetProjectileData(ProjectileData data)
	{
		_data = data;
		gameObject->AddComponent<Sprite>(data.sprite.c_str())->SetLayer(Layer::Projectiles);
		rigidbody->AddForce(data.direction * data.speed, ForceMode::IMPULSE);
	}

	const ProjectileData& GetProjectileData() const { return _data; }

private:
	ProjectileData _data{};
	Rigidbody* rigidbody = nullptr;
};