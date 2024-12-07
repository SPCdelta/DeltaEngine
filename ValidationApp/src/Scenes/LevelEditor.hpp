#pragma once

#include "Engine/Delta.hpp"
#include "Engine/UI/SnapToGridDraggable.hpp"

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

		float paddingTop = 50.0f;
		float padding = 5.0f;
		float paddingOutLeftUI = 30.0f;
		float paddingRightBarTop = padding * 2;

		float scaleInUIBar = 64.0f;
		float rightBarWidth = 100.0f;
		float imagespace = (scaleInUIBar + padding);
		float TopBarHeight = paddingTop + scaleInUIBar + 10.0f;

		float titleTopPadding = 12.0f;
		float titleWitdh = 80.f;
		float titleLeftPadding = windowWidth / 2 - titleWitdh / 2;
		float titleFontSize = 24.f;
		
		int maxOptionPerRow = (windowWidth - paddingOutLeftUI * 2 - rightBarWidth) / imagespace;
		int maxOptionPerCol =
			(windowHeight - TopBarHeight - paddingRightBarTop) / imagespace;

		float topBarLenght = imagespace * maxOptionPerRow;
		float rightBarstart = windowWidth - rightBarWidth;

		float saveFontSize = 20.f;

		std::shared_ptr<GameObject> saveButton{Instantiate({{rightBarstart - 20.0f, paddingTop * 1.2f}, 0.0f, {160.0f, saveFontSize}})};
		saveButton->AddComponent<Ui::Text>("Save Level", "knight", saveFontSize, Rendering::Color{0, 0, 0, 255})->SetBackground({255,255,255,255});

		saveButton->AddComponent<Ui::Button>()->SetOnLeftMouseClick([]() -> void { std::cout << "Level saved!!! test"; }, "UI");

		std::shared_ptr<GameObject> titleTxt{ Instantiate({{titleLeftPadding, titleTopPadding}, 0.0f, {titleWitdh, titleFontSize}}) };
		auto title = titleTxt->AddComponent<Ui::Text>("floor_tiles", "knight", titleFontSize, Rendering::Color{ 0, 0, 0, 255 });
		title->SetBackground({ 255,255,255,255 });

		std::shared_ptr<GameObject> layerTxt{ Instantiate({{titleLeftPadding + 160.f, titleTopPadding}, 0.0f, {titleWitdh, titleFontSize}}) };
		auto layer = layerTxt->AddComponent<Ui::Text>("Layer: " + LayerHelper::GetString(_layer), "knight", titleFontSize, Rendering::Color{ 0, 0, 0, 255 });
		layer->SetBackground({ 255,255,255,255 });
		layerWheel(layer);


		FillTopBar(title, maxOptionPerRow, scaleInUIBar, padding, paddingOutLeftUI, paddingTop);

		/*std::vector<std::shared_ptr<GameObject>> optionEnemies;

		index = 0;

		for (auto& pair : sprites)
		{
			if (maxOptionPerCol <= index)
				break;

			optionEnemies.emplace_back(Instantiate({{rightBarstart + padding * 3,  
				TopBarHeight + paddingRightBarTop + scaleInUIBar * index + padding * index},
				 0.0f,{scaleInUIBar, scaleInUIBar}}));

			optionEnemies.back()->AddComponent<Ui::Image>(pair.first.c_str());
			optionEnemies.back()->AddComponent<Ui::Button>()->SetOnLeftMouseClick(
				[this]() -> void {
					this->_tiles.emplace_back(
						Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}}));
				},
				"UI");
			index++;
		}*/

		BackgroundOfUI(windowWidth,windowHeight, TopBarHeight, rightBarstart, rightBarWidth);
	
	}

	void FillTopBar(Ui::Text* title, int maxOptionPerRow, float scaleInUIBar, float padding, float paddingOutLeftUI, float paddingTop)
	{

		std::map<std::string, SpriteData*> sprites = ResourceManager::GetSprites({ "floor_tiles" });
		std::vector<std::shared_ptr<GameObject>> optionTiles;

		int index = 0;

		title->SetText("Assets ..."); //TODO moet dus de type van de sprites zijn
		for (auto& pair : sprites)
		{
			if (maxOptionPerRow <= index)
				break;

			optionTiles.emplace_back(Instantiate({ { scaleInUIBar * index + padding * index + paddingOutLeftUI, paddingTop }, 0.0f,{ scaleInUIBar, scaleInUIBar } }));

			optionTiles.back()->AddComponent<Ui::Image>(pair.first);
			optionTiles.back()->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this, pair]() -> void {this->makeNewTile(pair.first);},"UI");
			index++;
		}
	}

	void layerWheel(Ui::Text* title){

		InputManager::onMouseWheel([this, title](Input& e) {
			int wheelDirection = 1;
			if (e.wheelVertically < 0)
				wheelDirection = -1;


			int layer = LayerHelper::GetInt(_layer);

			int newLayer = layer + wheelDirection;

			if (LayerHelper::InLayers(newLayer)){
				_layer = LayerHelper::GetLayer(newLayer);
				title->SetText("Layer: " + LayerHelper::GetString(_layer));
			}

		});

	}

	void makeNewTile(const std::string& spriteName){

		auto mousePos = InputManager::GetMousePosition();
		_tiles.emplace_back(Instantiate({ { mousePos.mouseX - 0.5f, mousePos.mouseY - 0.5f }, 0.0f,{ 1.0f, 1.0f } }));
		auto draggable = _tiles.back()->AddComponent<SnapToGridDraggable>();
		auto sprite = _tiles.back()->AddComponent<Sprite>(spriteName);

		sprite->SetLayer(Layer::Default);

		InputManager::onMouseWheel([draggable, sprite] (Input& e){
				if (!draggable->isBingDragged())
					return;

				/*int wheelDirection = 1;
				if (e.wheelVertically < 0)
					wheelDirection = -1;


				int layer = LayerHelper::GetInt(sprite->GetLayer());
				
				int newLayer = layer + wheelDirection;

				if (LayerHelper::InLayers(newLayer))
					sprite->SetLayer(LayerHelper::GetLayer(newLayer));*/

			});

	}

   private:
	std::vector<std::shared_ptr<GameObject>> _tiles;

	Layer _layer = Layer::Default;

	void BackgroundOfUI(float windowWitdh, float windowHeight, float topBarHight, float rightBarstart, float rightBarWith)
	{
		std::shared_ptr<GameObject> backgroundTopBar{ Instantiate({{0.0f, 0.0f}, 0.0f, {windowWitdh, topBarHight}})};
		backgroundTopBar->AddComponent<Ui::Image>("gray_rect")->SetColor({0, 0, 0, 0}); //TODO dit miss een rect maken inplaats van een image


		/*std::shared_ptr<GameObject> backgroundSideBar{Instantiate({{rightBarstart, topBarHight}, 0.0f, {rightBarWith, windowHeight - topBarHight}})};
		backgroundSideBar->AddComponent<Ui::Image>("gray_rect")->SetColor({0, 0, 0, 0});*/ //TODO dit miss een rect maken inplaats van een image

	}
};