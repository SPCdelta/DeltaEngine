#include "SceneManager.hpp"

void SceneManager::Load(const std::string& sceneName)
{
	auto it = _factories.find(sceneName);
	if (it != _factories.end())
	{
		_currentScene = it->second(sceneName);
		return;
	}
#ifdef _DEBUG
	std::cerr << "Scene doesnt exist!" << std::endl;
#else
	throw new std::exception("Scene with name '" + sceneName + "' doesnt exist!");
#endif
}
