#include "SceneManager.hpp"

std::shared_ptr<Scene> SceneManager::GetCurrent() const
{
	return _currentScene;
}

void SceneManager::Load(const std::string& sceneName)
{
	auto it = _factories.find(sceneName);
	if (it != _factories.end())
		_currentScene = it->second(sceneName);
}