#pragma once

#include <Engine/Delta.hpp>

struct ProjectileData
{
	std::string sprite;
	int damage;
	float speed;
	Math::Vector2 direction;
};

constexpr float DEFAULT_PROJECTILE_DESPAWN_TIME = 10.0f;

class Projectile : public BehaviourScript
{
public:
	~Projectile()
	{
		rigidbody = nullptr;
	}

	void OnStart() override;
	void OnUpdate() override;

	const ProjectileData& GetProjectileData() const { return _data; }

	void SetProjectileData(ProjectileData data)
	{
		gameObject->SetTag("projectile");
		_data = data;
		Sprite* sprite = gameObject->AddComponent<Sprite>(data.sprite.c_str());
		sprite->SetLayer(Layer::Projectiles);
		transform->rotation = Math::DirectionToAngle(data.direction);
		rigidbody->AddForce(data.direction * data.speed, ForceMode::IMPULSE);
	}

	Rigidbody* rigidbody = nullptr;

private:
	ProjectileData _data{};
};