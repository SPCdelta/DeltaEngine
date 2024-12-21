#pragma once

#include "Engine/Delta.hpp"
#include "Engine/UI/Scrollable.hpp"
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
    const std::vector<std::string> SPRITE_CATEGORY = { "floor_tiles", "wall_tiles", "player", "enemy_spawners" };
    const std::map<std::string, Layer> LAYER_MAP = { {"floor_tiles", Layer::Floor}, {"wall_tiles", Layer::Wall}, {"player", Layer::Player}, {"enemy_spawners" , Layer::Player} };

    // Constructor
    LevelEditor(const std::string& sceneName) : Scene(sceneName) {}

    void OnStart() override
    {
        ViewportData& viewport = GetWindow()->GetViewport();
        const int windowWidth = viewport.width;
        const int windowHeight = viewport.height;

        const float topBarHeight = PADDING_TOP + SCALE_IN_UI_BAR + 10.0f;
        const float titleLeftPadding = windowWidth / 2 - TITLE_WIDTH / 2;

        const float rightBarStart = windowWidth - RIGHT_BAR_WIDTH;

        _screenPort = { {0.0f, topBarHeight}, 0.0f, {static_cast<float>(windowWidth), windowHeight - topBarHeight} };
        
       Json::json data = RetriveUserData();
        if (data.contains("fileName") && !data["fileName"].empty()){
            _saveFileName = data["fileName"];
            DeleteUserData();
        }
        InitLevelEditor();

        UIBackButtonAndBinding(rightBarStart);
        UISaveButtonAndBinding(rightBarStart);
        UITopBarAndBinding(windowWidth, titleLeftPadding, topBarHeight);
        BindCamara();
    }



    void InitLevelEditor(){

        auto mousePos = InputManager::GetMousePosition();
        _brush = Instantiate({ {mousePos.GetX(), mousePos.GetY()}, 0.0f, {1.0f, 1.0f} });
        auto* brushComponnet = _brush->AddComponent<SnapToGridBrush>(
            [this](Transform& transform, Sprite* sprite)
            {
                auto& vector = _tiles;
                std::string spriteName = sprite->GetSprite();
            	
            	auto it = std::find_if(vector.begin(), vector.end(), [this, transform, spriteName](std::shared_ptr<GameObject>& e) {
            		if (e->transform->position == transform.position){
            			e->GetComponent<Sprite>().SetSprite(spriteName);
                        return true;
            		}
                    return false;
            	});

            	if (it == vector.end())
                    CreateTile(spriteName, sprite->GetSpriteData()->category);
            
            }); 
        brushComponnet->RemoveOnKey(KEY_E);
        brushComponnet->SetCanves(_screenPort);

        if (_saveFileName.empty()){
            MakeSaveFilePath();
            return;
        }
        FileManager fileManager;

        Json::json loadTiles = fileManager.Load(LEVEL_PATH + _saveFileName + ".json", "json");
        if (loadTiles.contains("tiles"))
        {
            for (size_t i = 0; i < loadTiles["tiles"].size(); ++i)
            {
                auto& jsonTile = loadTiles["tiles"][i];


                if (jsonTile.contains("transform") && jsonTile.contains("sprite") && jsonTile.contains("tag"))
                {
                    auto& tile = _tiles.emplace_back(Instantiate(TransformDTO::JsonToTransform(jsonTile)));
                    SpriteDTO spriteData = SpriteDTO::JsonToSpriteData(jsonTile);

                    tile->AddComponent<Sprite>(spriteData.spriteName)->SetLayer(spriteData.layer);
                    tile->SetTag(SPRITE_CATEGORY[0]);
                }
            }
        }
        if (loadTiles.contains(SPRITE_CATEGORY[2]))
        {
            auto& player = loadTiles[SPRITE_CATEGORY[2]];
            if (player.contains("transform") && player.contains("sprite") && player.contains("tag"))
            {
                auto& tile = _tiles.emplace_back(Instantiate(TransformDTO::JsonToTransform(player)));
                SpriteDTO spriteData = SpriteDTO::JsonToSpriteData(player);

                tile->AddComponent<Sprite>(spriteData.spriteName)->SetLayer(spriteData.layer);
                tile->SetTag(SPRITE_CATEGORY[2]);
            }
        }
    }
   
    //File handeling
    void SaveLevel(){

        FileManager fileManager;

        Json::json tilesJson;
        int tileCounter = 0;


        for (auto& tile : _tiles)
        {
            if (tile->GetTag() == SPRITE_CATEGORY[0]){//floor_tile
                auto& tileJson = tilesJson["tiles"][tileCounter];
                TransformDTO::ToJson(tileJson, tile->GetComponent<Transform>());
                SpriteDTO::ToJson(tileJson, tile->GetComponent<Sprite>());
                tileJson["tag"] = StringUtils::Split(tileJson["sprite"]["name"], '_')[0];
                tileCounter++;

            } else if (tile->GetTag() == SPRITE_CATEGORY[2]){ //player
                auto& tileJson = tilesJson["player"];
                TransformDTO::ToJson(tileJson, tile->GetComponent<Transform>());
                SpriteDTO::ToJson(tileJson, tile->GetComponent<Sprite>());
                tileJson["tag"] = StringUtils::Split(tileJson["sprite"]["name"], '_')[0];
            }
        }
        MakeSaveFilePath();
        fileManager.Save(_saveFilePath, "json", tilesJson);
    }

    void MakeSaveFilePath(){
        if (_saveFileName.empty()){
            auto fileNames = FileManager::filesInDirectory(LEVEL_PATH);
            _saveFileName = "level-" + std::to_string(fileNames.size() + 1);
        }
        
        _saveFilePath = LEVEL_PATH + _saveFileName + ".json";

    }


    void CreateTile(const std::string& spriteName, const std::string& category)
    {
        auto mousePos = InputManager::GetMousePosition();
        auto& tile = _tiles.emplace_back(Instantiate({ camera->ToWorldGrid(mousePos), 0.0f, {1.0f, 1.0f} }));

        tile->SetTag(category);

        auto sprite = tile->AddComponent<Sprite>(spriteName);
        sprite->SetLayer(LAYER_MAP.at(category));
    }

    void BindCamara()
    {
        float speed = 1.0f;
        _inputListeners.Add(InputManager::keyPressed(KEY_D, [this, speed](Input& e) {
            camera->AddToPosition({ speed,0.f });
            _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
            }));
        _inputListeners.Add(InputManager::keyPressed(KEY_A, [this, speed](Input& e) {
            camera->AddToPosition({ -speed,0.f });
            _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
            }));
        _inputListeners.Add(InputManager::keyPressed(KEY_S, [this, speed](Input& e) {
            camera->AddToPosition({ 0.f,-speed });
            _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
            }));
        _inputListeners.Add(InputManager::keyPressed(KEY_W, [this, speed](Input& e) {
            camera->AddToPosition({ 0.f,speed });
            _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
            }));
    }


    //UI/ Input Binding
    void UIBackButtonAndBinding(const float rightBarStart)
    {
        std::shared_ptr<GameObject> backButton{
            Instantiate({ { rightBarStart - 20.0f, PADDING_TOP }, 0.0f,{ 160.0f, SAVE_FONT_SIZE } })
        };
        auto* text = backButton->AddComponent<Ui::Text>("Back", "knight", SAVE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 }); 
        text->SetBackground({ 255, 255, 255, 255 });
        
        auto* button = backButton->AddComponent<Ui::Button>();
        button->SetOnLeftMouseClick([this]() {
            SaveLevel();
            LoadScene("LevelEditorLevelChose");
            }, "UI");
        button->SetOnMousePressed([text](){
            text->SetColor({80,80 ,80 });
            }, "UI");
    }

    void UISaveButtonAndBinding(const float rightBarStart)
    {
        std::shared_ptr<GameObject> saveButton{
            Instantiate({ { rightBarStart - 20.0f, PADDING_TOP * 1.7f }, 0.0f,{ 160.0f, SAVE_FONT_SIZE } })
        };
        auto* text = saveButton->AddComponent<Ui::Text>("Save Level", "knight", SAVE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        text->SetBackground({ 255, 255, 255, 255 });

        auto* button = saveButton->AddComponent<Ui::Button>();
        button->SetOnLeftMouseClick([this, text]() {
            SaveLevel();
            text->SetColor({ 0,0 ,0 });

            }, "UI");
        button->SetOnMousePressed([text]() {
            text->SetColor({ 80,80 ,80 });
            }, "UI");
    }

    int calculateSpritesInrow(std::unordered_map<std::string, std::vector<std::string>> categorySprites, int maxVisibleSprites){
        int amout = 0;
        if (categorySprites.contains(SPRITE_CATEGORY[_layerIndexTopBar]))
            amout = static_cast<int>(categorySprites.at(SPRITE_CATEGORY[_layerIndexTopBar]).size());

        return amout / maxVisibleSprites;
    }

    std::vector<std::string> GetVisibleSprites(std::unordered_map<std::string, std::vector<std::string>> categorySprites,
        int maxVisibleSprites,
        int direction)
    {
        std::vector<std::string> result;

        int maxtileIndexOptions = calculateSpritesInrow(categorySprites, maxVisibleSprites);

        _tileIndexOptions += direction;

        if (_tileIndexOptions < 0){
            _layerIndexTopBar -= 1;
            if (_layerIndexTopBar < 0)
                _layerIndexTopBar = SPRITE_CATEGORY.size() -1;
            
            _tileIndexOptions = calculateSpritesInrow(categorySprites, maxVisibleSprites);
            
        }
        else if (_tileIndexOptions > maxtileIndexOptions)
        {
            _layerIndexTopBar += 1;
            if (_layerIndexTopBar >= SPRITE_CATEGORY.size())
                _layerIndexTopBar = 0;

            _tileIndexOptions = 0;
        }

        std::vector<std::string> sprites;
        if (categorySprites.contains(SPRITE_CATEGORY[_layerIndexTopBar]))
            sprites = categorySprites.at(SPRITE_CATEGORY[_layerIndexTopBar]);


        for (size_t i = maxVisibleSprites * _tileIndexOptions; i < maxVisibleSprites * (_tileIndexOptions + 1) && i < sprites.size(); i++)
        {
            result.push_back(sprites[i]);
        }

        return result;
    }


    void UITopBarAndBinding(int windowWidth, float titleLeftPadding, float topBarHeight)
    {
        const float imagespace = (SCALE_IN_UI_BAR + PADDING);
        
        const int maxOptionPerRow = static_cast<int>((static_cast<float>(windowWidth) - PADDING_OUT_LEFT_UI * 2 - RIGHT_BAR_WIDTH) / imagespace);
        const float topBarLength = imagespace * maxOptionPerRow;
        
        std::shared_ptr<GameObject> titleTxt{ Instantiate({{titleLeftPadding, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto title = titleTxt->AddComponent<Ui::Text>(_saveFileName, "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        title->SetBackground({ 255, 255, 255, 255 });

        std::shared_ptr<GameObject> layerObj{ Instantiate({{titleLeftPadding + 160.0f, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto layerTxt = layerObj->AddComponent<Ui::Text>(SPRITE_CATEGORY[_layerIndexTopBar], "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        layerTxt->SetBackground({ 255, 255, 255, 255 });



        std::unordered_map<std::string, SpriteData*> sprites = ResourceManager::GetSprites(SPRITE_CATEGORY);
        std::unordered_map<std::string, std::vector<std::string>> categorySprites;
        
        for (const auto& pair : sprites) {
            const std::string& key = pair.first;
            const std::string& category = pair.second->category;

            categorySprites[category].push_back(key);
        }

        for (int i = 0; i < maxOptionPerRow; i++)
        {
            auto& optionTile = _optionTiles.emplace_back(Instantiate({
                        { -SCALE_IN_UI_BAR * 2, -SCALE_IN_UI_BAR * 2},
                        0.0f, {SCALE_IN_UI_BAR, SCALE_IN_UI_BAR} }));
            optionTile->AddComponent<Ui::Image>("default_texture");
            optionTile->AddComponent<BrushSprite>("default_texture", &_brush->GetComponent<SnapToGridBrush>());
        }

        auto lambdaChangeSprite = 
            [this, categorySprites, maxOptionPerRow, layerTxt](int wheelDirection) 
            {
            auto optionTilesVector = GetVisibleSprites(categorySprites, maxOptionPerRow, wheelDirection);
            layerTxt->SetText(SPRITE_CATEGORY[_layerIndexTopBar]);

            for (size_t i = 0; i < _optionTiles.size(); i++)
            {
                auto& optionTile = _optionTiles[i];
                if (optionTilesVector.size() <= i)
                {
                    optionTile->GetComponent<Transform>().position.Set({ -SCALE_IN_UI_BAR * 2, -SCALE_IN_UI_BAR * 2 });
                    continue;
                }
                const std::string spriteName = optionTilesVector[i];
                optionTile->GetComponent<Transform>().position.Set({ SCALE_IN_UI_BAR * i + PADDING * i + PADDING_OUT_LEFT_UI, PADDING_TOP });
                optionTile->GetComponent<Ui::Image>().SetSprite(spriteName);
                optionTile->GetComponent<BrushSprite>().SetSprite(spriteName);
            }

        };
        lambdaChangeSprite(0);


        std::shared_ptr<GameObject> TopBar{ Instantiate({{0.0f, 0.0f}, 0.0f, {static_cast<float>(windowWidth), topBarHeight}}) };
        TopBar->AddComponent<Ui::Scrollable>(lambdaChangeSprite);
    }

private:

    InputHandler _inputListeners;
    Transform _screenPort;

    std::string _saveFilePath;
    std::string _saveFileName;

    std::vector<std::shared_ptr<GameObject>> _tiles;
    std::vector<std::shared_ptr<GameObject>> _optionTiles;
    std::map<std::string, std::vector<std::shared_ptr<GameObject>>> _tileMapOptions;
    int _tileIndexOptions = 0;
    int _layerIndexTopBar = 0;

    std::shared_ptr<GameObject> _brush;


    Layer _layer = Layer::Default;

};
