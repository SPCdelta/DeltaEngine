#include "SceneManager.hpp"

std::shared_ptr<Scene> SceneManager::Load(std::string sceneName)
{
	for (auto& scene : scenes) {
		if (scene->getName() == sceneName) {
			std::cout << "Loading existing scene " << sceneName << std::endl;
			return scene;
		}
	}
	std::cout << "Creating and loading new scene " << sceneName << std::endl;
	auto newScene = std::make_shared<Scene>(sceneName);
	// instantiate() ?
	scenes.push_back(newScene);

	return newScene;
}
