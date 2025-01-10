#pragma once

#include "Engine/Delta.hpp"
#include "../UI/BaseUIScene.hpp"
#include "../Scripts/InputTest.hpp"
#include <vector>

class InputTestScene : public Scene
{
   public:
		InputTestScene(const std::string& sceneName) : Scene(sceneName) {
			//Instantiate({{200.0f, 200.0f}, 0.0f, {64.0f, 64.0f}})->AddComponent<InputTest>();
			int ButtonHeight = 100;
			float Margin = 5;
			int index = 1;
			std::shared_ptr<GameObject> deleteButtonObj = UIFactory::CreateButton(this,
				"X", "goblin", 16, Rendering::Color{ 255, 255, 255, 255 }, Layer::Button);
			deleteButtonObj->GetComponent<Ui::Button>().SetOnLeftMouseClick(
				[this, deleteButtonObj]() { DestroyObject(deleteButtonObj);}, "UI");
			deleteButtonObj->transformRef.scale = { ButtonHeight, ButtonHeight };
			deleteButtonObj->transformRef.position = Math::Vector2{ 0.0f, (ButtonHeight + Margin) * 1 };
			std::shared_ptr<GameObject> deleteButtonObj2 = UIFactory::CreateButton(this,
				"X", "goblin", 16, Rendering::Color{ 255, 255, 255, 255 }, Layer::Button);
			deleteButtonObj2->GetComponent<Ui::Button>().SetOnLeftMouseClick(
				[this, deleteButtonObj2]() { DestroyObject(deleteButtonObj2); }, "UI");
			deleteButtonObj2->transformRef.scale = { ButtonHeight, ButtonHeight };
			deleteButtonObj2->transformRef.position = Math::Vector2{ 0.0f, (ButtonHeight + Margin) * 2 };

		}

private:
};