#pragma once

#include <Engine/Delta.hpp>

#include "../Classes/MySceneData.hpp"

class SceneSwitchBehaviour : public BehaviourScript
{
public:
	void OnStart() override
	{
		std::cout << "OnStart: " << _current << std::endl;
	}

	void OnUpdate() override
	{
		if (_timer >= _switchAfter)
		{
			LoadScene(_switchTo);
		}
		_timer++;
	}

	void SetSwitchTo(const std::string& to, const std::string& current)
	{
		_switchTo = to;
		_current = current;
	}

private:
	std::string _switchTo{};
	std::string _current{};

	int _timer = 0;
	int _switchAfter = 150;
};

class Scene1 : public Scene
{
public:
	Scene1(const std::string& name) : Scene(name)
	{ }

	void OnStart() override
	{
		Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}})
			->AddComponent<SceneSwitchBehaviour>()
			->SetSwitchTo("Scene2", "Scene1");

		// Data
		Json::json& data = RetrieveUserData();

		if (data.empty())
		{
			StoreUserData({ {"a" , 5}, {"b", 12},{"C", "Hello!" } });
		}

		Json::json data2 = RetrieveUserData();
		std::cout << "User data: " << data2.dump(4) << std::endl;
	}
};

class Scene2 : public Scene
{
public:
	Scene2(const std::string& name) : Scene(name) 
	{ }

	void OnStart() override
	{
		Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}})
			->AddComponent<SceneSwitchBehaviour>()
			->SetSwitchTo("Scene1", "Scene2");

		// Data
		Json::json& data = RetrieveUserData();
		data["a"] = static_cast<int>(data["a"]) +  1;
		std::cout << "User data: " << data.dump(4) << std::endl;
	}
};