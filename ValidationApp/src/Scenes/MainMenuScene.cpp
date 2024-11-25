#include "MainMenuScene.hpp"
#include "../Scripts/TempAudio.hpp"
#include "Engine/Audio/MusicSource.hpp"
#include "Engine/Audio/SFXSource.hpp"

MainMenuScene::MainMenuScene(const std::string& sceneName) 
	: Scene(sceneName)
{
	std::shared_ptr<GameObject> menuImage{Instantiate({{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}})};
	//std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(menuImage->GetComponent<Transform>(), 4, 64, 64, 4, 1, 2, 3);
	menuImage->AddComponent<Sprite>("Assets\\Textures\\player.png");

	std::shared_ptr<GameObject> sheetedSprite{Instantiate({{1.0f, 1.0f}, 0.0f, {1.0f, 1.0f}})};
	//std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(sheetedSprite->GetComponent<Transform>(), 4, 64, 64, 4, 1, 2, 3);
	//sheetedSprite->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png", sheet);
	std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(sheetedSprite->GetComponent<Transform>(), 4, 64, 64, 0, 0, 0, 2);
	sheet->AddIdleAnimation(4, 1, 200);
	sheetedSprite->AddComponent<Sprite>("Assets\\Textures\\spritesheet3.png", sheet);
	sheetedSprite->AddComponent<MainMenuBehaviour>();

	std::shared_ptr<GameObject> musicObject{Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}})};
	musicObject->AddComponent<Audio::MusicSource>();
	musicObject->AddComponent<TempAudio>();
}
