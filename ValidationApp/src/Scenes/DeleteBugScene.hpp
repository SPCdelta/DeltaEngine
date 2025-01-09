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

	void OnStart() override
	{
		std::shared_ptr<GameObject> collider = Instantiate();
		collider->transformRef.scale = { 3.0f, 3.0f };
		collider->transformRef.position = { 4.0f, -1.5f };
		collider->AddComponent<Sprite>("player");
		collider->AddComponent<BoxCollider>();
		Rigidbody* rb = collider->AddComponent<Rigidbody>();
		rb->SetGravityScale(0.0f);
		rb->onTriggerEnter.Register([this](Collider& collider) { _collisions++; });
	}

	void OnUpdate() override
	{
		if (_timer <= 0.0f)
		{
			_timer = 0.5f;
			std::cout << "Spawns: " << _spawnCount << " | Collisions: " << _collisions << std::endl;
			for (size_t i = 0; i < 1; i++)
			{
				//std::shared_ptr<GameObject> myObject = Instantiate
				//(
				//	{
				//		{
				//			Math::Random::NextFloat(-1.0f, 1.0f),
				//			Math::Random::NextFloat(-1.0f, 1.0f)
				//		}, 
				//		Math::Random::NextFloat(0.0f, 360.0f),
				//		{ 1.0f, 1.0f }
				//	}
				//);
				std::shared_ptr<GameObject> myObject = Instantiate
				(
					{
						{
							0.0f,
							0.0f
						}, 
						0.0f,
						{ 1.0f, 1.0f }
					}
				);
				myObject->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, { 1.0f, 0.0f }});
				//myObject->AddComponent<Sprite>("arrow");

				//myObject->AddComponent<Lifetime>(2.0f);
				//myObject->AddComponent<Velocity>(3.0f, 0.0f);
				_spawnCount++;
			}
		}
		else
		{
			_timer -= Time::GetDeltaTime();
		}

		//if (_spawnCount % 100 == 0)
		//{
		//	std::cout << "Arrow" << _spawnCount << std::endl;
		//	std::cout << "Collisions: " << _collisions << std::endl;
		//}
	}

private:
	int _spawnCount{0};
	int _collisions{0};
	float _timer{0.0f};
};