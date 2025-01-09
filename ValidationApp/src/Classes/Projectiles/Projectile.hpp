#pragma once

#include <Engine/Delta.hpp>

struct ProjectileData
{
	std::string sprite;
	int damage;
	float speed;
	Math::Vector2 direction;
};

constexpr float DEFAULT_PROJECTILE_DESPAWN_TIME = 1.0f;

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
		transform->gameObject->SetTag("projectile");
		_data = data;
		Sprite* sprite = transform->gameObject->AddComponent<Sprite>(data.sprite);
		sprite->SetLayer(Layer::Projectiles);
		transform->rotation = Math::DirectionToAngle(data.direction);

		rigidbody->AddForce(data.direction * data.speed, ForceMode::IMPULSE);
		rigidbody->SetVelocity(data.direction * data.speed);
		//transform->gameObject->AddComponent<Velocity>();
	}

	Rigidbody* rigidbody = nullptr;

private:
	ProjectileData _data{};
	float _timeAlive = DEFAULT_PROJECTILE_DESPAWN_TIME;
};