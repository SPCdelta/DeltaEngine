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
			myObject->transformRef.position = 
			{
				Math::Random::NextFloat(-1.0f, 1.0f),
				Math::Random::NextFloat(-1.0f, 1.0f)
			};
			myObject->transformRef.rotation = Math::Random::NextFloat(0.0f, 360.0f);

			myObject->AddComponent<Sprite>("arrow");
			_spawnCount++;

			_objects.push_back(myObject.get());
			_objectsLifespan.emplace(myObject.get(), 0.0f);
		}

		if (_spawnCount % 100 == 0)
		{
			std::cout << "Arrow" << _spawnCount << std::endl;
		}

		for (GameObject* gameObject : _objects)
		{
			if (_objectsLifespan[gameObject] >= 1.0f)
			{
				for (size_t i = 0; i < _objects.size(); i++)
				{
					if (_objects[i] == gameObject)
					{
						_objects.erase(_objects.begin() + i);
						_objectsLifespan.erase(gameObject);
						break;
					}
				}
				DestroyObject(gameObject);
			}

			_objectsLifespan[gameObject] += Time::GetDeltaTime();
			gameObject->transformRef.position += {(1.0f * Time::GetDeltaTime()), 0.0f};
			//std::cout << gameObject->transformRef.position.GetX() << " : " << gameObject->transformRef.position.GetY() << std::endl;
		}
	}

private:
	int _spawnCount{ 0 };
	std::vector<GameObject*> _objects{};
	std::unordered_map<GameObject*, float> _objectsLifespan;
};