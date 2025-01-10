#include "Projectile.hpp"

Projectile::~Projectile()
{
	rigidbody = nullptr;
}

void Projectile::OnStart() 
{

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
	transform->gameObject->SetTag("projectile");
	_data = data;
	Sprite* sprite = transform->gameObject->AddComponent<Sprite>(data.sprite);
	sprite->SetLayer(Layer::Projectiles);
	transform->rotation = Math::DirectionToAngle(data.direction);
	transform->gameObject->AddComponent<Velocity>(data.direction * data.speed);
}