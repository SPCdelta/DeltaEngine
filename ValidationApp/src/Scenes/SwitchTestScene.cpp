#include "SwitchTestScene.hpp"

void SceneSwitchBehaviour::OnStart()
{
	std::cout << "OnStart: " << _current << std::endl;
}

void SceneSwitchBehaviour::OnUpdate()
{
	if (_timer >= _switchAfter)
	{
		LoadScene(_switchTo);
	}
	_timer++;
}

void SceneSwitchBehaviour::SetSwitchTo(const std::string& to, const std::string& current)
{
	_switchTo = to;
	_current = current;
}

Scene1::Scene1(const std::string& name) 
	: Scene(name)
{ 

}

void Scene1::OnStart()
{
	Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}})->AddComponent<SceneSwitchBehaviour>()->SetSwitchTo("Scene2", "Scene1");

	// Data
	Json::json& data = RetriveUserData();

	if (data.empty())
	{
		StoreUserData({ {"a" , 5}, {"b", 12},{"C", "Hello!" } });
	}

	Json::json data2 = RetriveUserData();
	std::cout << "User data: " << data2.dump(4) << std::endl;
}

Scene2::Scene2(const std::string& name) 
	: Scene(name) 
{ 

}

void Scene2::OnStart()
{
	Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}})->AddComponent<SceneSwitchBehaviour>()->SetSwitchTo("Scene1", "Scene2");

	// Data
	Json::json& data = RetriveUserData();
	data["a"] = static_cast<int>(data["a"]) +  1;
	std::cout << "User data: " << data.dump(4) << std::endl;
}