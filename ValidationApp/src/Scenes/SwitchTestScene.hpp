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
			MySceneData* data = SceneHelper::GetSceneData<MySceneData>(gameObject->_scene);
			LoadScene(_switchTo, data);
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
		MySceneData* data = SceneHelper::GetSceneData<MySceneData>(this);
		if (data == nullptr)
		{
			data = new MySceneData{ 5, 12, "Hello!" };
			SceneHelper::SetSceneData<MySceneData>(this, data);
		}

		MySceneData* dataAgain = SceneHelper::GetSceneData<MySceneData>(this);
		dataAgain->Print();
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
		MySceneData* dataAgain = SceneHelper::GetSceneData<MySceneData>(this);
		dataAgain->_a += 1;
		if (dataAgain != nullptr)
		{
			dataAgain->Print();
		}
	}
};