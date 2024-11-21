#pragma once
#include "Scene.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

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

	std::shared_ptr<Scene> GetCurrent() const { return _currentScene; }

	void Load(const std::string& sceneName);

	// ?
	// std::unique_ptr<Scene> ExportScene();

private:
	std::unordered_map<std::string, std::function<std::shared_ptr<Scene>(const std::string&)>> _factories;
	std::shared_ptr<Scene> _currentScene;
};