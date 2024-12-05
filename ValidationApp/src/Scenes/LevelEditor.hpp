#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/MouseFollowBehaviour.hpp"
#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"

#include <vector>

class LevelEditor : public Scene
{
   public:
	LevelEditor(const std::string& sceneName) : Scene(sceneName) {}


	void OnStart() override {

		auto viewport = GetWindow()->GetViewport();
		int windowWidth = viewport.width;
		int windowHeight = viewport.height;

		float paddingTop = 10.0f;
		float padding = 5.0f;
		float paddingOutLeftUI = 30.0f;
		float paddingRightBarTop = padding * 2;

		float scaleInUIBar = 64.0f;
		float rightBarWidth = 100.0f;
		float imagespace = (scaleInUIBar + padding);
		float TopBarHeight = paddingTop + scaleInUIBar + 10.0f;
		
		int maxOptionPerRow = (windowWidth - paddingOutLeftUI * 2 - rightBarWidth) / imagespace;
		int maxOptionPerCol =
			(windowHeight - TopBarHeight - paddingRightBarTop) / imagespace;

		float topBarLenght = imagespace * maxOptionPerRow;
		float rightBarstart = windowWidth - rightBarWidth;

		float textFontSize = 16.f;

		std::shared_ptr<GameObject> saveButton{Instantiate({{rightBarstart - 20.0f, paddingTop * 3.5f}, 0.0f, {80.0f, textFontSize}})};
		saveButton->AddComponent<Ui::Text>("Save Level!", "knight", Rendering::Color{0, 0, 0, 255})->SetBackground({255,255,255,255});

		saveButton->AddComponent<Ui::Button>()->SetOnLeftMouseClick([]() -> void { std::cout << "Level saved!!! test"; }, "UI");




		std::map<std::string, SpriteData*>& sprites = ResourceManager::GetAllSprites();
		std::vector<std::shared_ptr<GameObject>> optionTiles;

		int index = 0;

		for (auto& pair : sprites)
		{
			if (maxOptionPerRow <= index)
				break;

			optionTiles.emplace_back(
				Instantiate({{scaleInUIBar * index + padding * index +
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

		std::vector<std::shared_ptr<GameObject>> optionEnemies;

		index = 0;

		for (auto& pair : sprites)
		{
			if (maxOptionPerCol <= index)
				break;

			optionEnemies.emplace_back(Instantiate({{rightBarstart + padding * 3,  
				TopBarHeight + paddingRightBarTop + scaleInUIBar * index + padding * index},
				 0.0f,
				 {scaleInUIBar, scaleInUIBar}}));
			optionEnemies.back()->AddComponent<Ui::Image>(pair.first.c_str());
			optionEnemies.back()->AddComponent<Ui::Button>()->SetOnLeftMouseClick(
				[this]() -> void {
					this->_tiles.emplace_back(
						Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}}));
				},
				"UI");
			index++;
		}

		BackgroundOfUI(windowWidth,windowHeight, TopBarHeight, rightBarstart, rightBarWidth);
	
	}

   private:
	std::vector<std::shared_ptr<GameObject>> _tiles;

	void BackgroundOfUI(float windowWitdh, float windowHeight, float topBarHight, float rightBarstart, float rightBarWith)
	{
		std::shared_ptr<GameObject> backgroundTopBar{ Instantiate({{0.0f, 0.0f}, 0.0f, {windowWitdh, topBarHight}})};
		backgroundTopBar->AddComponent<Ui::Image>("gray_rect")->SetColor({0, 0, 0, 0}); //TODO dit miss een rect maken inplaats van een image


		std::shared_ptr<GameObject> backgroundSideBar{Instantiate({{rightBarstart, topBarHight}, 0.0f, {rightBarWith, windowHeight - topBarHight}})};
		backgroundSideBar->AddComponent<Ui::Image>("gray_rect")->SetColor({0, 0, 0, 0}); //TODO dit miss een rect maken inplaats van een image

	}
};