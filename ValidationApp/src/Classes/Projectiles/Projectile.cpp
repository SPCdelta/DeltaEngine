#include "Projectile.hpp"

Projectile::~Projectile()
{
	rigidbody = nullptr;
}

void Projectile::OnStart() 
{
	if (transform && transform->gameObject && transform->gameObject->HasComponent<Rigidbody>())
	{
		rigidbody = &transform->gameObject->GetComponent<Rigidbody>();
		rigidbody->onTriggerEnter.Register([this](Collider& collider)
		{ 
			if (transform && transform->gameObject && collider.transform.gameObject && collider.transform.gameObject->GetTag() == "rect" && 
				collider.transform.gameObject->HasComponent<Sprite>() && collider.transform.gameObject->GetComponent<Sprite>().GetVisible() && 
				transform->gameObject->HasComponent<Sprite>())
			{
				transform->gameObject->GetComponent<Sprite>().SetVisible(false);
			}		
		});
	}
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