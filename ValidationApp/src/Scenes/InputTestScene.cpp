#include "InputTestScene.hpp"

InputTestScene::InputTestScene(const std::string& sceneName) 
	: Scene(sceneName)
{
	Instantiate({{200.0f, 200.0f}, 0.0f, {64.0f, 64.0f}})->AddComponent<InputTest>();
}