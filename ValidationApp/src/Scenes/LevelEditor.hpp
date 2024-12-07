#pragma once

#include "Engine/Delta.hpp"
#include "Engine/UI/SnapToGridDraggable.hpp"
#include "Engine/UI/Scrollable.hpp"

#include "../Scripts/MouseFollowBehaviour.hpp"
#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"

#include <vector>

class LevelEditor : public Scene
{
public:
    // Constructor
    LevelEditor(const std::string& sceneName) : Scene(sceneName) {}

    // Constants
    static constexpr float PADDING_TOP = 50.0f;
    static constexpr float PADDING = 5.0f;
    static constexpr float PADDING_OUT_LEFT_UI = 30.0f;
    static constexpr float PADDING_RIGHT_BAR_TOP = PADDING * 2;
    static constexpr float SCALE_IN_UI_BAR = 64.0f;
    static constexpr float RIGHT_BAR_WIDTH = 100.0f;
    static constexpr float TITLE_TOP_PADDING = 12.0f;
    static constexpr float TITLE_WIDTH = 80.0f;
    static constexpr float TITLE_FONT_SIZE = 24.0f;
    static constexpr float SAVE_FONT_SIZE = 20.0f;

    void OnStart() override
    {
        const auto viewport = GetWindow()->GetViewport();
        const int windowWidth = viewport.width;
        const int windowHeight = viewport.height;

        const float topBarHeight = PADDING_TOP + SCALE_IN_UI_BAR + 10.0f;
        const float titleLeftPadding = windowWidth / 2 - TITLE_WIDTH / 2;

        const float rightBarStart = windowWidth - RIGHT_BAR_WIDTH;

        // Save Button
        std::shared_ptr<GameObject> saveButton{
            Instantiate({{rightBarStart - 20.0f, PADDING_TOP * 1.2f}, 0.0f, {160.0f, SAVE_FONT_SIZE}})
        };
        saveButton->AddComponent<Ui::Text>("Save Level", "knight", SAVE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 })->SetBackground({ 255, 255, 255, 255 });
        saveButton->AddComponent<Ui::Button>()->SetOnLeftMouseClick([]() -> void {
            std::cout << "Level saved!!! test";
            }, "UI");

        LayerChanger(titleLeftPadding, topBarHeight, windowWidth, windowHeight);
        TopBar(windowWidth, titleLeftPadding);
        BackgroundOfUI(windowWidth, windowHeight, topBarHeight, rightBarStart);
    }

    void LayerChanger(float titleLeftPadding, float topBarHeight, int windowWidth, int windowHeight)
    {
        std::shared_ptr<GameObject> layerTxt{ Instantiate({{titleLeftPadding + 160.0f, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto layer = layerTxt->AddComponent<Ui::Text>("Layer: " + LayerHelper::GetString(_layer), "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        layer->SetBackground({ 255, 255, 255, 255 });

        std::shared_ptr<GameObject> worldView{ Instantiate({{0.0f, topBarHeight}, 0.0f, {static_cast<float>(windowWidth), windowHeight - topBarHeight}}) };
        worldView->AddComponent<Ui::Scrollable>([this, layer](int wheelDirection) -> void {
            int layerInt = LayerHelper::GetInt(_layer);

            int newLayer = layerInt + wheelDirection;

            if (LayerHelper::InLayers(newLayer)) {
                _layer = LayerHelper::GetLayer(newLayer);
                layer->SetText("Layer: " + LayerHelper::GetString(_layer));
            }
            });
    }

    void TopBar(int windowWidth, float titleLeftPadding)
    {

        const float imagespace = (SCALE_IN_UI_BAR + PADDING);
        
        const int maxOptionPerRow = (windowWidth - PADDING_OUT_LEFT_UI * 2 - RIGHT_BAR_WIDTH) / imagespace;
        const float topBarLength = imagespace * maxOptionPerRow;
        
        std::shared_ptr<GameObject> titleTxt{ Instantiate({{titleLeftPadding, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto title = titleTxt->AddComponent<Ui::Text>("floor_tiles", "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        title->SetBackground({ 255, 255, 255, 255 });

        std::map<std::string, SpriteData*> sprites = ResourceManager::GetSprites({ "floor_tiles" });
        std::vector<std::shared_ptr<GameObject>> optionTiles;

        int index = 0;

        title->SetText("Assets ..."); // TODO: Change to sprite type
        for (auto& pair : sprites) {
            if (maxOptionPerRow <= index)
                break;

            optionTiles.emplace_back(Instantiate({ 
                {SCALE_IN_UI_BAR * index + PADDING * index + PADDING_OUT_LEFT_UI, PADDING_TOP},
                0.0f, {SCALE_IN_UI_BAR, SCALE_IN_UI_BAR} }));

            optionTiles.back()->AddComponent<Ui::Image>(pair.first);
            optionTiles.back()->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this, pair]() -> void {
                this->makeNewTile(pair.first);
                }, "UI");
            index++;
        }
    }

    void makeNewTile(const std::string& spriteName)
    {
        auto mousePos = InputManager::GetMousePosition();
        _tiles.emplace_back(Instantiate({ {mousePos.mouseX - 0.5f, mousePos.mouseY - 0.5f}, 0.0f, {1.0f, 1.0f} }));
        auto draggable = _tiles.back()->AddComponent<SnapToGridDraggable>();
        auto sprite = _tiles.back()->AddComponent<Sprite>(spriteName);

        sprite->SetLayer(_layer);

        InputManager::onMouseWheel([this, draggable, sprite](Input& e) {
            if (!draggable->isBingDragged())
                return;
            sprite->SetLayer(_layer);
            });
    }

private:
    std::vector<std::shared_ptr<GameObject>> _tiles;

    Layer _layer = Layer::Default;

    void BackgroundOfUI(float windowWidth, float windowHeight, float topBarHeight, float rightBarStart)
    {
        std::shared_ptr<GameObject> backgroundTopBar{ Instantiate({{0.0f, 0.0f}, 0.0f, {windowWidth, topBarHeight}}) };
        backgroundTopBar->AddComponent<Ui::Image>("gray_rect")->SetColor({ 0, 0, 0, 0 }); // TODO: Replace with a rectangle

        // Uncomment if needed:
        /*
        std::shared_ptr<GameObject> backgroundSideBar{Instantiate({{rightBarStart, topBarHeight}, 0.0f, {rightBarWidth, windowHeight - topBarHeight}})};
        backgroundSideBar->AddComponent<Ui::Image>("gray_rect")->SetColor({0, 0, 0, 0}); // TODO: Replace with a rectangle
        */
    }
};
