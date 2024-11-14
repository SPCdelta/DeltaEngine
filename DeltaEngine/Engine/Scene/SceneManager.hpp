#pragma once
#include "Scene.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class SceneManager {
public:
	std::shared_ptr<Scene> Load(std::string sceneName);
private: 
	std::vector<std::shared_ptr<Scene>> scenes;
	Scene currentScene;
};