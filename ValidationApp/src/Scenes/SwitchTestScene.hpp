#pragma once

#include <Engine/Delta.hpp>

class SceneSwitchBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	void SetSwitchTo(const std::string& to, const std::string& current);

private:
	std::string _switchTo{};
	std::string _current{};

	int _timer = 0;
	int _switchAfter = 150;
};

class Scene1 : public Scene
{
public:
	Scene1(const std::string& name);

	void OnStart() override;
};

class Scene2 : public Scene
{
public:
	Scene2(const std::string& name);

	void OnStart() override;
};