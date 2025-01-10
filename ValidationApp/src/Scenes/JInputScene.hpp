#pragma once

#include <Engine/Delta.hpp>

#include "../UI/BaseUIScene.hpp"

class JInputScene : public Scene
{
public:
	JInputScene(const std::string& sceneName) 
		: Scene(sceneName)
	{

	}

	void OnStart() override
	{
		std::shared_ptr<GameObject> buttonObj = UIFactory::CreateButton(
			this, "JInput", "goblin", 32, Rendering::Color{255, 0, 0, 255},
			Layer::Button);
		Ui::Button& button = buttonObj->GetComponent<Ui::Button>();
		button.SetOnLeftMouseClick(
			[this]() 
			{ 
				std::cout << "Clicked!" << std::endl;
			},
			"jinput"
		);
	}
};