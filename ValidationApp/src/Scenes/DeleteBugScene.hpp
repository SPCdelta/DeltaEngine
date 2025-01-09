#pragma once

#include <Engine/Delta.hpp>

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
									{ _collisions++; });
	}

	void OnUpdate() override
	{
		for (size_t i = 0; i < 1; i++)
		{
			std::shared_ptr<GameObject> myObject = Instantiate();
			myObject->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, { 1.0f, 0.0f }});
			myObject->transformRef.position = 
			{
				Math::Random::NextFloat(-1.0f, 1.0f),
				Math::Random::NextFloat(-1.0f, 1.0f)
			};
			myObject->transformRef.rotation = Math::Random::NextFloat(0.0f, 360.0f);

			//myObject->AddComponent<Sprite>("arrow");

			//myObject->AddComponent<Lifetime>(2.0f);
			//myObject->AddComponent<Velocity>(3.0f, 0.0f);
			_spawnCount++;
		}

		if (_spawnCount % 100 == 0)
		{
			std::cout << "Arrow" << _spawnCount << std::endl;
			std::cout << "Collisions: " << _collisions << std::endl;
		}
	}

private:
	int _spawnCount{0};
	int _collisions{0};
};