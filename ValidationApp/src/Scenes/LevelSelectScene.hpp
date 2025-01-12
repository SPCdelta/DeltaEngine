#pragma once

#include "../UI/BaseUIScene.hpp"
#include "../Classes/LevelManager.hpp"
#include "LevelScene.hpp"
#include "../UI/UIFactory.hpp"

class LevelSelectScene : public BaseUIScene
{
public:
	LevelSelectScene(const std::string& name);

	void OnStart() override;

private:
	std::vector<GameObject*> _buttons;

	void Refresh();

	void CreateLevelsList();
	void CreateLevelButton(size_t index, std::string levelName);
};