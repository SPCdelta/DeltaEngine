#pragma once

#include "Engine/Delta.hpp"
#include "Engine/UI/SnapToGridDraggable.hpp"
#include "Engine/UI/Scrollable.hpp"

#include "../Scripts/MouseFollowBehaviour.hpp"
#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"

#include <vector>
#include <map>

class LevelEditor : public Scene
{
public:

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

    const std::string LEVEL_PATH = "Assets\\Level\\";
    const std::vector<std::string> SPRITE_CATEGORY = { "floor_tiles" , "player" };

    // Constructor
    LevelEditor(const std::string& sceneName) : Scene(sceneName) {
        _saveFileName = "level-1";

        _saveFilePath = LEVEL_PATH + _saveFileName + ".json";

        auto allLayers = LayerHelper::GetAllLayer();

        for (auto& layer : allLayers)
        {
            _tilesPerLayer.insert(std::make_pair(layer, std::vector<std::shared_ptr<GameObject>>{}));
        }

    }

    void InitLevelEditor(const std::string& level){

        if (level.empty()){
            MakeSaveFilePath();
            return;
        }
        FileManager fileManager;

        Json::json loadTiles = fileManager.Load(LEVEL_PATH + level + ".json", "json");
        if (loadTiles.contains("tiles"))
        {
            for (size_t i = 0; i < loadTiles["tiles"].size(); ++i)
            {
                auto& tile = loadTiles["tiles"][i];


                if (tile.contains("transform") && tile.contains("sprite") && tile.contains("tag"))
                {
                    Layer layer = static_cast<Layer>(tile["sprite"]["layer"]);
                    _layer = layer;
                    CreateLevelEditorTile(tile["sprite"]["name"], tile["sprite"]["name"], TransformDTO::JsonToTransform(tile));
                    _tilesPerLayer[_layer].back()->SetTag(SPRITE_CATEGORY[0]);
                    _tilesPerLayer[_layer].back()->GetComponent<SnapToGridDraggable>().SetDraggeble(false);
                }
            }
        }
        if (loadTiles.contains(SPRITE_CATEGORY[1]))
        {
            auto& player = loadTiles[SPRITE_CATEGORY[1]];
            if (player.contains("transform") && player.contains("sprite") && player.contains("tag"))
            {
                Layer layer = static_cast<Layer>(player["sprite"]["layer"]);
                _layer = layer;
                CreateLevelEditorTile(player["sprite"]["name"], player["sprite"]["name"], TransformDTO::JsonToTransform(player));
                _tilesPerLayer[_layer].back()->SetTag(SPRITE_CATEGORY[1]);
                _tilesPerLayer[_layer].back()->GetComponent<SnapToGridDraggable>().SetDraggeble(false);
            }
        }
    }


    void OnStart() override
    {
        ViewportData& viewport = GetWindow()->GetViewport();
        const int windowWidth = viewport.width;
        const int windowHeight = viewport.height;

        const float topBarHeight = PADDING_TOP + SCALE_IN_UI_BAR + 10.0f;
        const float titleLeftPadding = windowWidth / 2 - TITLE_WIDTH / 2;

        const float rightBarStart = windowWidth - RIGHT_BAR_WIDTH;

        InitLevelEditor(_saveFileName);

        UIBackButtonAndBinding(rightBarStart);
        UISaveButtonAndBinding(rightBarStart);
        BindLayerChangerToMouseWheel(titleLeftPadding, topBarHeight, windowWidth, windowHeight);
        UITopBarAndBinding(windowWidth, titleLeftPadding, topBarHeight);
        BindCamara();
    }

   
    //File handeling
    void SaveLevel(){

        FileManager fileManager;

        Json::json tilesJson;
        int tileCounter = 0;

        for (auto& [layer, tiles] : _tilesPerLayer)
        {
            for (auto& tile : tiles)
            {
                if (tile->GetTag() == SPRITE_CATEGORY[0]){//floor_tile
                    auto& tileJson = tilesJson["tiles"][tileCounter];
                    TransformDTO::ToJson(tileJson, tile->GetComponent<Transform>());
                    tileJson["sprite"]["name"] = tile->GetComponent<Sprite>().GetSprite();
                    tileJson["tag"] = String::split(tileJson["sprite"]["name"], '_')[0];
                    tileJson["sprite"]["layer"] = tile->GetLayer();
                    tileCounter++;

                } else if (tile->GetTag() == SPRITE_CATEGORY[1]){ //player
                    auto& tileJson = tilesJson["player"];
                    TransformDTO::ToJson(tileJson, tile->GetComponent<Transform>());
                    tileJson["sprite"]["name"] = tile->GetComponent<Sprite>().GetSprite();
                    tileJson["tag"] = String::split(tileJson["sprite"]["name"], '_')[0];
                    tileJson["sprite"]["layer"] = tile->GetLayer();
                }
            }

        }
        fileManager.Save(_saveFilePath, "json", tilesJson);
    }

    void MakeSaveFilePath(){
        auto fileNames = FileManager::filesInDirectory(LEVEL_PATH);
        _saveFileName = "level-" + std::to_string(fileNames.size() + 1);
        
        _saveFilePath = LEVEL_PATH + _saveFileName + ".json";

    }


    //Create
    void CreateLevelEditorTile(const std::string& spriteName, const std::string& category, Transform transform) {
        _tilesPerLayer[_layer].emplace_back(Instantiate(transform));
        CreateLevelEditorTile(spriteName, category, false);

    }

    void CreateLevelEditorTile(const std::string& spriteName, const std::string& category, bool mousePos = true)
    {
        if (mousePos) {
            auto mousePos = InputManager::GetMousePosition();
            _tilesPerLayer[_layer].emplace_back(Instantiate({ {mousePos.GetX(), mousePos.GetY()}, 0.0f, {1.0f, 1.0f} }));
        }

        auto& tile = _tilesPerLayer[_layer].back();
        tile->SetTag(category);
        auto draggable = tile->AddComponent<SnapToGridDraggable>();
        auto sprite = tile->AddComponent<Sprite>(spriteName);
        sprite->SetLayer(_layer);

        draggable->activate("Ui:layer - " + LayerHelper::GetString(_layer), [this, sprite]() {
            sprite->SetLayer(_layer);
            });

        draggable->RemoveOnKey(KEY_Q, [this, tile]() {
            tile->Destroy(tile.get());
            });

        _inputs.push_back(InputManager::onMouseWheel([this, draggable, sprite](Input& e) {
            if (!draggable->isBingDragged())
                return;
            sprite->SetLayer(_layer);
            draggable->SetCategory("Ui:layer - " + LayerHelper::GetString(_layer));
            }));
    }


    //Input Binding
    void BindLayerChangerToMouseWheel(float titleLeftPadding, float topBarHeight, int windowWidth, int windowHeight)
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

    void BindCamara()
    {
        float speed = 0.3f;
        _inputs.push_back(InputManager::keyPressed(KEY_D, [this, speed](Input& e) {
            _camera->AddToPosition({ speed,0.f });
            }));
        _inputs.push_back(InputManager::keyPressed(KEY_A, [this, speed](Input& e) {
            _camera->AddToPosition({ -speed,0.f });
            }));
        _inputs.push_back(InputManager::keyPressed(KEY_S, [this, speed](Input& e) {
            _camera->AddToPosition({ 0.f,-speed });
            }));
        _inputs.push_back(InputManager::keyPressed(KEY_W, [this, speed](Input& e) {
            _camera->AddToPosition({ 0.f,speed });
            }));
    }


    //UI/ Input Binding
    void UIBackButtonAndBinding(const float rightBarStart)
    {
        std::shared_ptr<GameObject> saveButton{
            Instantiate({ { rightBarStart - 20.0f, PADDING_TOP }, 0.0f,{ 160.0f, SAVE_FONT_SIZE } })
        };
        saveButton->AddComponent<Ui::Text>("Back", "knight", SAVE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 })->SetBackground({ 255, 255, 255, 255 });
        saveButton->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this]() {
            LoadScene("LevelEditorLevelChose");
            }, "UI");
    }

    void UISaveButtonAndBinding(const float rightBarStart)
    {
        std::shared_ptr<GameObject> saveButton{
            Instantiate({ { rightBarStart - 20.0f, PADDING_TOP * 1.7f }, 0.0f,{ 160.0f, SAVE_FONT_SIZE } })
        };
        saveButton->AddComponent<Ui::Text>("Save Level", "knight", SAVE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 })->SetBackground({ 255, 255, 255, 255 });
        saveButton->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this]() {
            SaveLevel();
            std::cout << "Saved Level: ";
            }, "UI");
    }

    void UITopBarAndBinding(int windowWidth, float titleLeftPadding, float topBarHeight)
    {
        const float imagespace = (SCALE_IN_UI_BAR + PADDING);
        
        const int maxOptionPerRow = (windowWidth - PADDING_OUT_LEFT_UI * 2 - RIGHT_BAR_WIDTH) / imagespace;
        const float topBarLength = imagespace * maxOptionPerRow;
        
        std::shared_ptr<GameObject> titleTxt{ Instantiate({{titleLeftPadding, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto title = titleTxt->AddComponent<Ui::Text>("Level: " + _saveFileName, "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
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
                    CreateLevelEditorTile(key, value->category);
                }, "UI:Leveleditor-" + key);
        }

        auto lambdaChangeSprite = [this, sprites, maxOptionPerRow, maxtileIndexOptions](int wheelDirection) {

            HiddeOptionTiles();
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


    ~LevelEditor()
    {
        CleanUp();
    }

private:
    
    void HiddeOptionTiles(){
        for (auto& option : _optionTiles)
        {
            option->transform->position.Set({ -SCALE_IN_UI_BAR, -SCALE_IN_UI_BAR });
            option->GetComponent<Ui::Button>().SetPosition({ -SCALE_IN_UI_BAR, -SCALE_IN_UI_BAR });

        }
    }

    void CleanUp(){
        for (auto& input : _inputs)
        {
            InputManager::GetInstance().remove(input);
        }
        _inputs.clear();
    }


    std::string _saveFilePath;
    std::string _saveFileName;

    //std::vector<std::shared_ptr<GameObject>> _tiles;
    std::map<Layer, std::vector<std::shared_ptr<GameObject>>> _tilesPerLayer;
    std::vector<std::shared_ptr<GameObject>> _optionTiles;
    int _tileIndexOptions = 0;

    std::vector<InputLocation> _inputs;

    Layer _layer = Layer::Default;

};
