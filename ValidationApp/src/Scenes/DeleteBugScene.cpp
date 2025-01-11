#include "DeleteBugScene.hpp"

void DeleteBugBehaviour::OnUpdate() 
{

}

void DeleteBugBehaviour::TestBug() 
{

}

DeleteBugScene::DeleteBugScene(const std::string& name) 
	: Scene(name) 
{

}

void DeleteBugScene::OnStart()
{
	std::shared_ptr<GameObject> collider = Instantiate();
	collider->transformRef.scale = {3.0f, 3.0f};
	collider->transformRef.position = {4.0f, -1.5f};
	collider->AddComponent<Sprite>("player");
	collider->AddComponent<BoxCollider>();

	Rigidbody* rb = collider->AddComponent<Rigidbody>();
	rb->SetGravityScale(0.0f);
	rb->onTriggerEnter.Register(
	[this](Collider& collider)
	{
		if (IsColliding(collider))
			return;

		_collisions++;
		currentColliders.push_back(std::make_shared<Collider>(collider));
	});
}

bool DeleteBugScene::IsColliding(Collider& collider)
{
	for (auto& col : currentColliders)
	{
		if (EnginePhysics::AreEqual(col->GetId(), collider.GetId()))
			return true;
	}
	return false;
}

void DeleteBugScene::OnUpdate()
{
	_spawnTime -= Time::GetDeltaTime();
	if (CanSpawn())
	{
		for (size_t i = 0; i < 1; i++)
		{
			std::shared_ptr<GameObject> myObject = Instantiate();
			myObject->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, {1.0f, 0.0f}});
			myObject->AddComponent<Lifetime>(2.0f);
			myObject->transformRef.position = 
			{
				Math::Random::NextFloat(-1.0f, 1.0f),
				Math::Random::NextFloat(-1.0f, 1.0f)
			};

			_spawnCount++;
		}

		if (_spawnCount % 10 == 0)
		{
			std::cout << "Arrow" << _spawnCount << std::endl;
			std::cout << "Collisions: " << _collisions << std::endl;
		}

		StartSpawn();
	}
}

void DeleteBugScene::StartSpawn()
{
	_spawnTime = _spawnDuration / Time::GetMultiplier();
}

bool DeleteBugScene::CanSpawn() const
{
	return _spawnTime <= 0.0f;
}