#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/InputTest.hpp"

class InputTestScene : public Scene
{
   public:
		InputTestScene(const std::string& sceneName) : Scene(sceneName) {
			//Instantiate({{200.0f, 200.0f}, 0.0f, {64.0f, 64.0f}})->AddComponent<InputTest>();
			InputManager::onKeyPressed(
				KEY_P, [this](Input& key) { 
					LoadScene("MainMenuScene"); 
					std::cout << "P";
				}, "test");
		}
};