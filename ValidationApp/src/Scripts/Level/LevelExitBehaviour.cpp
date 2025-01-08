#include "LevelExitBehaviour.hpp"

LevelExitBehaviour::LevelExitBehaviour(const std::string& exitName)
	: _exitName{exitName}
{

}

void LevelExitBehaviour::OnStart()
{
	BoxCollider* collider = gameObject->AddComponent<BoxCollider>();
	collider->SetTrigger(true);
	gameObject->SetTag("level_exit");
}

void LevelExitBehaviour::SetExit(const std::string& exitName)
{
	_exitName = exitName;
}

const std::string& LevelExitBehaviour::GetExit() const
{
	return _exitName;
}