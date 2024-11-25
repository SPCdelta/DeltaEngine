#include "MainMenuScene.hpp"
#include "../Scripts/TempAudio.hpp"
#include "Engine/Audio/MusicSource.hpp"
#include "Engine/Audio/SFXSource.hpp"

MainMenuScene::MainMenuScene(const std::string& sceneName) 
	: Scene(sceneName)
{
	std::shared_ptr<GameObject> menuImage{Instantiate({{0.0f, 0.0f}, 0.0f, {200.0f, 200.0f}})};
	std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(menuImage->GetComponent<Transform>(), 4, 64, 64, 4, 1, 2, 3);
	menuImage->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png", sheet);
	menuImage->AddComponent<MainMenuBehaviour>();

	std::shared_ptr<GameObject> musicObject{Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}})};
	musicObject->AddComponent<Audio::MusicSource>();
	musicObject->AddComponent<TempAudio>();
}
