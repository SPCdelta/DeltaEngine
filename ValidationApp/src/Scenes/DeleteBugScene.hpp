#pragma once

#include <Engine/Delta.hpp>

class DeleteBugBehaviour : public BehaviourScript
{
public:
	void OnUpdate() override
	{
		if (_counter >= 1)
		{
			Destroy(gameObject);
		}
		_counter++;
	}

	void TestBug()
	{

	}

private:
	size_t _counter = 0;
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

	}

	void OnUpdate() override
	{
		for (size_t i = 0; i < 1; i++)
		{
			std::shared_ptr<GameObject> myObject = Instantiate();
			myObject->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, { 1.0f, 0.0f }});
			//DeleteBugBehaviour* behaviour = myObject->AddComponent<DeleteBugBehaviour>();
			//behaviour->TestBug();
			myObject->transformRef.position = 
			{
				Math::Random::NextFloat(-1.0f, 1.0f),
				Math::Random::NextFloat(-1.0f, 1.0f)
			};
			myObject->transformRef.rotation = Math::Random::NextFloat(0.0f, 360.0f);

			//myObject->AddComponent<Sprite>("arrow");
			_spawnCount++;
		}

		if (_spawnCount % 100 == 0)
		{
			std::cout << "Arrow" << _spawnCount << std::endl;
		}
	}

private:
	int _spawnCount{ 0 };
};