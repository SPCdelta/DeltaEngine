#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "Scene.hpp"
#include "../Core/Events/EventDispatcher.hpp"

class SceneManager 
{
public:
	template<typename T>
	void RegisterScene(const std::string& sceneName)
	{
		_factories[sceneName] = [](const std::string& sceneName)
		{
			return std::make_shared<T>(sceneName);
		};
	}

	std::shared_ptr<Scene> GetCurrent() const;

	void Load(const std::string& sceneName);

private:
	std::unordered_map<std::string, std::function<std::shared_ptr<Scene>(const std::string&)>> _factories;
	std::shared_ptr<Scene> _currentScene;
	std::shared_ptr<Scene> _previousScene;
};