#pragma once

#include <Engine/Delta.hpp>

class LevelExitBehaviour : public BehaviourScript
{
public:
	LevelExitBehaviour(const std::string& exitName) 
		: _exitName{ exitName }
	{

	}

	void OnStart() override
	{ 
		BoxCollider* collider = gameObject->AddComponent<BoxCollider>();
		collider->SetTrigger(true);
		gameObject->SetTag("level_exit");
	}

	void SetExit(const std::string& exitName) { _exitName = exitName; }
	const std::string& GetExit() const { return _exitName; }
	virtual void Use() { LoadScene(_exitName); }

private:
	std::string _exitName = "";
};