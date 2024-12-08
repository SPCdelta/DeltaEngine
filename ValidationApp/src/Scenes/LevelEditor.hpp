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

    const std::vector<std::string> SPRITE_CATEGORY = { "floor_tiles" , "player" };

    void OnStart() override
    {
        const auto viewport = GetWindow()->GetViewport();
        const int windowWidth = viewport.width;
        const int windowHeight = viewport.height;

        const float topBarHeight = PADDING_TOP + SCALE_IN_UI_BAR + 10.0f;
        const float titleLeftPadding = windowWidth / 2 - TITLE_WIDTH / 2;

        const float rightBarStart = windowWidth - RIGHT_BAR_WIDTH;

        SaveButton(rightBarStart);
        LayerChanger(titleLeftPadding, topBarHeight, windowWidth, windowHeight);
        TopBar(windowWidth, titleLeftPadding, topBarHeight);
    }

    void SaveButton(const float rightBarStart)
    {
        std::shared_ptr<GameObject> saveButton{
            Instantiate({ { rightBarStart - 20.0f, PADDING_TOP * 1.2f }, 0.0f,{ 160.0f, SAVE_FONT_SIZE } })
        };
        saveButton->AddComponent<Ui::Text>("Save Level", "knight", SAVE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 })->SetBackground({ 255, 255, 255, 255 });
        saveButton->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this]() {
            SaveLevel();
            }, "UI");
    }

    void SaveLevel(){

        FileManager fileManager;

        Json::json tilesJson;
        for (size_t i = 0; i < _tiles.size(); i++)
        {
            if (_tiles[i]->GetTag() == SPRITE_CATEGORY[0]){//floor_tile
                auto& tileJson = tilesJson["tiles"][i];
                TransformDTO::ToJson(tileJson, _tiles[i]->GetComponent<Transform>());
                tileJson["spriteName"] = _tiles[i]->GetComponent<Sprite>().GetSprite();
                tileJson["tag"] = tileJson["spriteName"];
                tileJson["layer"] = _tiles[i]->GetLayer();
            } else if (_tiles[i]->GetTag() == SPRITE_CATEGORY[1]){ //player
                auto& tileJson = tilesJson["player"];
                TransformDTO::ToJson(tileJson["transform"], _tiles[i]->GetComponent<Transform>());
                tileJson["spriteName"] = _tiles[i]->GetComponent<Sprite>().GetSprite();
                tileJson["tag"] = tileJson["spriteName"];
                tileJson["layer"] = _tiles[i]->GetLayer();
            }

        }
        fileManager.Save("Assets\\Files\\LevelEditor.json", "json", tilesJson);

    }

    void LayerChanger(float titleLeftPadding, float topBarHeight, int windowWidth, int windowHeight)
    {
        std::shared_ptr<GameObject> layerTxt{ Instantiate({{titleLeftPadding + 160.0f, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto layer = layerTxt->AddComponent<Ui::Text>("Layer: " + LayerHelper::GetString(_layer), "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        layer->SetBackground({ 255, 255, 255, 255 });

        std::shared_ptr<GameObject> worldView{ Instantiate({{0.0f, topBarHeight}, 0.0f, {static_cast<float>(windowWidth), windowHeight - topBarHeight}}) };
        worldView->AddComponent<Ui::Scrollable>([this, layer](int wheelDirection) {
            int layerInt = LayerHelper::GetInt(_layer);

            int newLayer = layerInt + wheelDirection;

            if (LayerHelper::InLayers(newLayer)) {
                //InputManager::deactivateCategory("Ui:layer - " + LayerHelper::GetString(_layer));
                _layer = LayerHelper::GetLayer(newLayer);
                
                //InputManager::activateCategory("Ui:layer - " + LayerHelper::GetString(_layer));

                layer->SetText("Layer: " + LayerHelper::GetString(_layer));
            }

        });
    }



    void TopBar(int windowWidth, float titleLeftPadding, float topBarHeight)
    {

        const float imagespace = (SCALE_IN_UI_BAR + PADDING);
        
        const int maxOptionPerRow = (windowWidth - PADDING_OUT_LEFT_UI * 2 - RIGHT_BAR_WIDTH) / imagespace;
        const float topBarLength = imagespace * maxOptionPerRow;
        
        std::shared_ptr<GameObject> titleTxt{ Instantiate({{titleLeftPadding, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto title = titleTxt->AddComponent<Ui::Text>("Tiles", "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        title->SetBackground({ 255, 255, 255, 255 });

        std::unordered_map<std::string, SpriteData*> sprites = ResourceManager::GetSprites(SPRITE_CATEGORY);

        int maxtileIndexOptions = sprites.size() / maxOptionPerRow;

        for (auto& [key, value] : sprites)
        {
            _optionTiles.emplace_back(Instantiate({
                    {-SCALE_IN_UI_BAR, -SCALE_IN_UI_BAR},
                    0.0f, {SCALE_IN_UI_BAR, SCALE_IN_UI_BAR} }));


            _optionTiles.back()->AddComponent<Ui::Image>(key);
            _optionTiles.back()->AddComponent<Ui::Button>()->SetOnLeftMouseClick(
                [this, key, value]() {
                    makeNewTile(key, value->category);
                }, "UI:Leveleditor-" + key);
        }

        auto lambdaChangeSprite = [this, sprites, maxOptionPerRow, maxtileIndexOptions](int wheelDirection) {

            CleanOptionTiles();
            auto startIt = sprites.begin();

            _tileIndexOptions += wheelDirection;
            if (_tileIndexOptions < 0)
                _tileIndexOptions = maxtileIndexOptions;
            else if (_tileIndexOptions > maxtileIndexOptions)
                _tileIndexOptions = 0;

            std::advance(startIt, maxOptionPerRow * _tileIndexOptions);

            int index = 0;
            for (auto pair = startIt; pair != sprites.end() && index < maxOptionPerRow; ++pair) {

                auto tileoption = _optionTiles.at(maxOptionPerRow * _tileIndexOptions + index);

                tileoption->transform->position.Set({ SCALE_IN_UI_BAR * index + PADDING * index + PADDING_OUT_LEFT_UI, PADDING_TOP });
                tileoption->GetComponent<Ui::Button>().SetPosition({ SCALE_IN_UI_BAR * index + PADDING * index + PADDING_OUT_LEFT_UI, PADDING_TOP });

                index++;
            }

        };
        lambdaChangeSprite(0);


        std::shared_ptr<GameObject> TopBar{ Instantiate({{0.0f, 0.0f}, 0.0f, {static_cast<float>(windowWidth), topBarHeight}}) };
        //TopBar->AddComponent<Ui::Image>("gray_rect")->SetColor({ 0, 0, 0, 0 });
        TopBar->AddComponent<Ui::Scrollable>(lambdaChangeSprite);

    }

    void makeNewTile(const std::string& spriteName, const std::string& category)
    {
        auto mousePos = InputManager::GetMousePosition();
        _tiles.emplace_back(Instantiate({ {mousePos.mouseX - 0.5f, mousePos.mouseY - 0.5f}, 0.0f, {1.0f, 1.0f} }));
        auto& tile = _tiles.back();
        tile->SetTag(category);
        auto draggable = tile->AddComponent<SnapToGridDraggable>();
        auto sprite = tile->AddComponent<Sprite>(spriteName);
        sprite->SetLayer(_layer);

        draggable->activate("Ui:layer - " + LayerHelper::GetString(_layer), [this, sprite](){
            sprite->SetLayer(_layer);
            });

        draggable->RemoveOnKey(KEY_Q, [this, tile](){
            tile->Destroy(tile.get());
            });

        InputManager::onMouseWheel([this, draggable, sprite](Input& e) {
            if (!draggable->isBingDragged())
                return;
            sprite->SetLayer(_layer);
            draggable->SetCategory("Ui:layer - " + LayerHelper::GetString(_layer));
            });
    }

private:
    
    void CleanOptionTiles(){
        for (auto& option : _optionTiles)
        {
            option->transform->position.Set({ -SCALE_IN_UI_BAR, -SCALE_IN_UI_BAR });
            option->GetComponent<Ui::Button>().SetPosition({ -SCALE_IN_UI_BAR, -SCALE_IN_UI_BAR });

        }
    }

    std::vector<std::shared_ptr<GameObject>> _tiles;
    std::vector<std::shared_ptr<GameObject>> _optionTiles;
    int _tileIndexOptions = 0;

    Layer _layer = Layer::Default;

};
