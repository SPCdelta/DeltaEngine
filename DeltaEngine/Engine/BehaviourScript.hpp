#pragma once

#include <string>

#include "GameObject.hpp"
//class GameObject;

class BehaviourScript
{
public:
	friend class GameObject;

	virtual void OnStart() { };
	virtual void OnUpdate() { };

	void LoadScene(const std::string& name) { gameObject->LoadScene(name); }

	virtual ~BehaviourScript() = default;

	GameObject* gameObject = nullptr;
	Camera* camera = nullptr;
};

