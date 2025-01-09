#pragma once

#include <Engine/Delta.hpp>
#include "../Classes/Projectiles/Projectile.hpp"

class DeleteBugBehaviour : public BehaviourScript
{
public:
	void OnUpdate() override
	{
		
	}

	void TestBug()
	{

	}

private:

};

class DeleteBugScene : public Scene
{
public:
	DeleteBugScene(const std::string& name)
		: Scene(name)
	{
		
	}

	std::vector<std::shared_ptr<Collider>> currentColliders;

	void OnStart() override
	{
		std::shared_ptr<GameObject> collider = Instantiate();
		collider->transformRef.scale = { 3.0f, 3.0f };
		collider->transformRef.position = { 4.0f, -1.5f };
		collider->AddComponent<Sprite>("player");
		collider->AddComponent<BoxCollider>();
		Rigidbody* rb = collider->AddComponent<Rigidbody>();
		rb->SetGravityScale(0.0f);
		rb->onTriggerEnter.Register([this](Collider& collider)			
		{ 
			if (IsColliding(collider))
				return;

			_collisions++; 
			currentColliders.push_back(std::make_shared<Collider>(collider));
		});
	}

	bool IsColliding(Collider& collider)
	{
		for (auto& col : currentColliders)
		{
			if (EnginePhysics::AreEqual(col->GetId(), collider.GetId()))
				return true;
		}
		return false;
	}

	void OnUpdate() override
	{
		_spawnTime -= Time::GetDeltaTime();

		if (CanSpawn())
		{
			for (size_t i = 0; i < 1; i++)
			{
				std::shared_ptr<GameObject> myObject = Instantiate();
				myObject->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, { 1.0f, 0.0f }});
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

private:
	int _spawnCount{0};
	int _collisions{0};

	float _spawnTime{0.0f};
	float _spawnDuration{1.0f};

	void StartSpawn()
	{
		_spawnTime = _spawnDuration / Time::GetMultiplier();
	}

	bool CanSpawn() const
	{
		return _spawnTime <= 0.0f;
	}
};