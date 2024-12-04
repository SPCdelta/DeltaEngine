#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/MouseFollowBehaviour.hpp"
#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"

#include <vector>

class LevelEditor : public Scene
{
   public:
	LevelEditor(const std::string& sceneName) : Scene(sceneName)
	{

		Window* window = GetWindow();
		int windowWidth = 1280;	 // todo dit van de window krijgen
		//int windowWidth, windowHeight;
		//auto window = GetWindow();
		//Rendering::GetWindowSize(*window, &windowWidth,
		//						 &windowHeight);

		float paddingTop = 10.0f;
		float rightPadding = 5.0f;
		float paddingOutLeftUI = 30.0f;

		float scaleInUIBar = 64.0f;
		float rightBarWidth = 100.0f;

		float imagespace = (scaleInUIBar + rightPadding);
		int maxOptionPerRow =
			(windowWidth - paddingOutLeftUI * 2 - rightBarWidth) / imagespace;
		float UILenght = imagespace * maxOptionPerRow;

		std::shared_ptr<GameObject> saveButton{Instantiate({{100.0f, 100.0f}, 0.0f, {100.0f, 100.0f}})};
		//saveButton->AddComponent<Ui::Image>("default_texture")->SetColor({255, 255, 255, 255});
		saveButton->AddComponent<Ui::Text>("Save Level!",
										   "Assets\\Fonts\\knight_warrior.otf",
										   Rendering::Color{0, 0, 0, 0})->SetFontSize(16);

		saveButton->AddComponent<Ui::Button>()->SetOnLeftMouseClick(
			[]() -> void { std::cout << "Level saved!!! test"; }, "UI");

		std::map<std::string, SpriteData*>& sprites =
			ResourceManager::GetAllSprites();
		std::vector<std::shared_ptr<GameObject>> optionTiles;

		int index = 0;

		for (auto& pair : sprites)
		{
			if (maxOptionPerRow <= index)
				break;

			optionTiles.emplace_back(
				Instantiate({{scaleInUIBar * index + rightPadding * index +
								  paddingOutLeftUI,
							  paddingTop},
							 0.0f,
							 {scaleInUIBar, scaleInUIBar}}));
			optionTiles.back()->AddComponent<Ui::Image>(pair.first.c_str());
			optionTiles.back()->AddComponent<Ui::Button>()->SetOnLeftMouseClick(
				[this]() -> void {
					this->_tiles.emplace_back(
						Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}}));
				},
				"UI");
			index++;
		}

		// Create Player
		/*std::shared_ptr<GameObject> playerObject{ Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		std::shared_ptr<AnimationSheet> sheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 4, 64, 64, 0, 0, 0, 2);
		sheet->AddIdleAnimation(4, 1, 200);
		playerObject->AddComponent<Sprite>("spritesheet3", sheet);

		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();

		playerObject->AddComponent<PlayerBehaviour>();

		std::shared_ptr<GameObject> skeletonObject{ Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		skeletonObject->AddComponent<Sprite>("spritesheet2");

		std::shared_ptr<GameObject> pokemonObject{ Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		pokemonObject->AddComponent<Sprite>("spritesheet");

		pokemonObject->SetLayer(Layer::Foreground);
		skeletonObject->SetLayer(Layer::Default);
		playerObject->SetLayer(Layer::Background);*/
	}

   private:
	std::vector<std::shared_ptr<GameObject>> _tiles;
};