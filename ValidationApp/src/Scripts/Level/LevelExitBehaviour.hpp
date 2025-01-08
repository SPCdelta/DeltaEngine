#pragma once

#include <Engine/Delta.hpp>

class LevelExitBehaviour : public BehaviourScript
{
public:
	LevelExitBehaviour(const std::string& exitName);

	void OnStart() override;

	void SetExit(const std::string& exitName);
	const std::string& GetExit() const;

	virtual void Use() 
	{ 
		LoadScene(_exitName); 
	}

private:
	std::string _exitName = "";
};