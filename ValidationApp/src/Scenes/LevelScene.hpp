#pragma once

#include <Engine/Delta.hpp>

#include "../Scripts/PlayerBehaviour.hpp"

struct LevelSceneData
{
	std::string name;
};

class LevelScene : public Scene
{
public:
	LevelScene(const std::string& name) : Scene(name) {}

	void OnStart() override;

private:
	bool LoadLevel(const std::string& levelName);
};