#include "Projectile.hpp"

Projectile::~Projectile()
{
	rigidbody = nullptr;
}

void Projectile::OnStart() 
{
	gameObject->AddComponent<Despawner>(DEFAULT_PROJECTILE_DESPAWN_TIME);
	gameObject->AddComponent<CircleCollider>()->SetTrigger(true);
	rigidbody = gameObject->AddComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
}

void Projectile::OnUpdate()
{
	
}

const ProjectileData& Projectile::GetProjectileData() const
{
	return _data;
}

void Projectile::SetProjectileData(ProjectileData data)
{
	gameObject->SetTag("projectile");
	_data = data;
	Sprite* sprite = gameObject->AddComponent<Sprite>(data.sprite.c_str());
	sprite->SetLayer(Layer::Projectiles);
	transform->rotation = Math::DirectionToAngle(data.direction);
	rigidbody->AddForce(data.direction * data.speed, ForceMode::IMPULSE);
}