#include "LevelEditor.hpp"

LevelEditor::LevelEditor(const std::string& sceneName) 
    : Scene(sceneName) 
{

}

void LevelEditor::OnStart()
{
    ViewportData& viewport = GetWindow()->GetViewport();
    const int windowWidth = viewport.width;
    const int windowHeight = viewport.height;

    const float topBarHeight = PADDING_TOP + SCALE_IN_UI_BAR + 10.0f;
    const float titleLeftPadding = windowWidth / 2 - TITLE_WIDTH / 2;

    const float rightBarStart = windowWidth - RIGHT_BAR_WIDTH;

     _screenPort = { {0.0f, topBarHeight}, 0.0f, {static_cast<float>(windowWidth), windowHeight - topBarHeight} };
        
    Json::json data = RetrieveUserData();
    if (data.contains("levelName") && !data["levelName"].empty())
    {
        _saveFileName = data["levelName"];
        DeleteUserData();
    }
    
    InitLevelEditor();

    UIBackButtonAndBinding(rightBarStart);
    UISaveButtonAndBinding(rightBarStart);
    UITopBarAndBinding(windowWidth, 20, topBarHeight);
    BindCamera();
}

void LevelEditor::InitLevelEditor()
{
    auto mousePos = InputManager::GetMousePosition();
    _brush = Instantiate({ {mousePos.GetX(), mousePos.GetY()}, 0.0f, {1.0f, 1.0f} });
    auto* brushComponnet = _brush->AddComponent<SnapToGridBrush>
    (
        [this](Transform& transform, Sprite* sprite)
        {
            auto& vector = _tiles;
            std::string spriteName = sprite->GetSprite();
            
            auto it = std::find_if(vector.begin(), vector.end(), [this, transform, spriteName](std::shared_ptr<GameObject>& e) 
            {
                if (e->transform->position == transform.position)
                {
                    Sprite& sprite = e->GetComponent<Sprite>();
                    sprite.SetSprite(spriteName);
                    sprite.SetLayer(LAYER_MAP.at(sprite.GetSpriteData()->category));
                    e->SetTag(sprite.GetSpriteData()->category);
                    return true;
                }
                return false;
            });

            if (it == vector.end())
                CreateTile(spriteName, sprite->GetSpriteData()->category);
        
        }
    ); 
    brushComponnet->RemoveOnKey(KEY_E);
    brushComponnet->SetCanvas(_screenPort);

    if (_saveFileName.empty())
    {
        MakeSaveFilePath();
        return;
    }

    FileManager fileManager;
    Json::json loadTiles = fileManager.Load(LEVEL_PATH + _saveFileName, "json");

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
        loadTiles.erase(SPRITE_CATEGORY[2]);
    } 

    for (auto& tileType : SPRITE_CATEGORY)
        CreateTilesFromJson(loadTiles, tileType);
}

void LevelEditor::CreateTilesFromJson(Json::json& loadTiles, const std::string& jsonarray)
{
    if (!loadTiles.contains(jsonarray))
            return;

    for (size_t i = 0; i < loadTiles[jsonarray].size(); ++i)
    {
        auto& jsonTile = loadTiles[jsonarray][i];
        if (jsonTile.contains("transform") && jsonTile.contains("sprite") && jsonTile.contains("tag"))
        {
            auto& tile = _tiles.emplace_back(Instantiate(TransformDTO::JsonToTransform(jsonTile)));
            SpriteDTO spriteData = SpriteDTO::JsonToSpriteData(jsonTile);

            tile->AddComponent<Sprite>(spriteData.spriteName)->SetLayer(spriteData.layer);
            tile->SetTag(jsonarray);
        }
    }
}
   
void LevelEditor::SaveLevel()
{
    FileManager fileManager;
    Json::json tilesJson;

    int tileCounter = 0;
    for (auto& tile : _tiles)
    {
        if (tile->GetTag() == SPRITE_CATEGORY[2]) // Player
        {
            auto& tileJson = tilesJson["player"];
            TransformDTO::ToJson(tileJson, tile->GetComponent<Transform>());
            SpriteDTO::ToJson(tileJson, tile->GetComponent<Sprite>());
            tileJson["tag"] = StringUtils::Split(tileJson["sprite"]["name"], '_')[0];
        }
        else // Other
        {
            Json::json jsonObject;
            TransformDTO::ToJson(jsonObject, tile->GetComponent<Transform>());
            SpriteDTO::ToJson(jsonObject, tile->GetComponent<Sprite>());
            jsonObject["tag"] = StringUtils::Split(jsonObject["sprite"]["name"], '_')[0];
            tilesJson[tile->GetTag()].push_back(jsonObject);
        }
    }

    MakeSaveFilePath();
    fileManager.Save(_saveFilePath, "json", tilesJson);
}

void LevelEditor::MakeSaveFilePath()
{
    if (_saveFileName.empty())
    {
        int level = Random::NextInt(0, INT16_MAX);
        _saveFileName = "level-" + std::to_string(level) + ".json";
    }
    
    _saveFilePath = LEVEL_PATH + _saveFileName;
}


void LevelEditor::CreateTile(const std::string& spriteName, const std::string& category)
{
    auto mousePos = InputManager::GetMousePosition();
    auto& tile = _tiles.emplace_back(Instantiate({ camera->ToWorldGrid(mousePos), 0.0f, {1.0f, 1.0f} }));

    tile->SetTag(category);

    auto sprite = tile->AddComponent<Sprite>(spriteName);
    sprite->SetLayer(LAYER_MAP.at(category));
}

void LevelEditor::BindCamera()
{
    float speed = 1.0f;

    _inputListeners.Add(InputManager::keyPressed(KEY_D, [this, speed](Input& e) 
    {
        camera->AddToPosition({ speed,0.f });
        _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
    }));

    _inputListeners.Add(InputManager::keyPressed(KEY_A, [this, speed](Input& e) 
    {
        camera->AddToPosition({ -speed,0.f });
        _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
    }));

    _inputListeners.Add(InputManager::keyPressed(KEY_S, [this, speed](Input& e) 
    {
        camera->AddToPosition({ 0.f,-speed });
        _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
    }));

    _inputListeners.Add(InputManager::keyPressed(KEY_W, [this, speed](Input& e) 
    {
        camera->AddToPosition({ 0.f,speed });
        _brush->GetComponent<SnapToGridBrush>().NotifyTransform();
    }));
}

void LevelEditor::UIBackButtonAndBinding(const float rightBarStart)
{
    std::shared_ptr<GameObject> backButton
    {
        Instantiate({ { rightBarStart - 20.0f, PADDING_TOP }, 0.0f,{ 160.0f, SAVE_FONT_SIZE } })
    };

    auto* text = backButton->AddComponent<Ui::Text>("Back", "goblin", SAVE_FONT_SIZE, Rendering::Color{ 255, 255, 255, 255 }); 
    
    auto* button = backButton->AddComponent<Ui::Button>();
    button->SetOnLeftMouseClick([this]() 
    {
        SaveLevel();
        LoadScene("LevelEditorMenuScene");
    }, "UI");

    button->SetOnMousePressed([text]()
    {
        text->SetColor({80,80 ,80 });
    }, "UI");
}

void LevelEditor::UISaveButtonAndBinding(const float rightBarStart)
{
    std::shared_ptr<GameObject> saveButton
    {
        Instantiate({ { rightBarStart - 20.0f, PADDING_TOP * 1.7f }, 0.0f,{ 160.0f, SAVE_FONT_SIZE } })
    };

    auto* text = saveButton->AddComponent<Ui::Text>("Save", "goblin", SAVE_FONT_SIZE, Rendering::Color{ 255, 255, 255, 255 });

    auto* button = saveButton->AddComponent<Ui::Button>();
    button->SetOnLeftMouseClick([this, text]() 
    {
        SaveLevel();
        text->SetColor({ 255, 255, 255 });
    }, "UI");

    button->SetOnMousePressed([text]() 
    {
        text->SetColor({ 80, 80, 80 });
    }, "UI");
}

int LevelEditor::CalculateSpritesInrow(std::unordered_map<std::string, std::vector<std::string>> categorySprites, int maxVisibleSprites)
{
    int amount = 0;
    if (categorySprites.contains(SPRITE_CATEGORY[_layerIndexTopBar]))
        amount = static_cast<int>(categorySprites.at(SPRITE_CATEGORY[_layerIndexTopBar]).size());
    return amount / maxVisibleSprites;
}

 std::vector<std::string> LevelEditor::GetVisibleSprites(std::unordered_map<std::string, std::vector<std::string>> categorySprites, int maxVisibleSprites, 
     int direction)
{
    std::vector<std::string> result;
    int maxtileIndexOptions = CalculateSpritesInrow(categorySprites, maxVisibleSprites);

    _tileIndexOptions += direction;
    if (_tileIndexOptions < 0)
    {
        _layerIndexTopBar -= 1;
        if (_layerIndexTopBar < 0)
			_layerIndexTopBar = static_cast<int>(SPRITE_CATEGORY.size() - 1);      
        _tileIndexOptions = CalculateSpritesInrow(categorySprites, maxVisibleSprites);         
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
        result.push_back(sprites[i]);
    return result;
}

void LevelEditor::UITopBarAndBinding(int windowWidth, float titleLeftPadding, float topBarHeight)
{
    const float imagespace = (SCALE_IN_UI_BAR + PADDING);
        
    const int maxOptionPerRow = static_cast<int>((static_cast<float>(windowWidth) - PADDING_OUT_LEFT_UI * 2 - RIGHT_BAR_WIDTH) / imagespace);
    const float topBarLength = imagespace * maxOptionPerRow;
    
    std::shared_ptr<GameObject> titleTxt{ Instantiate({{titleLeftPadding, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
    auto title = titleTxt->AddComponent<Ui::Text>(_saveFileName, "goblin", TITLE_FONT_SIZE, Rendering::Color{ 255, 255, 255, 255 });

    Vector2 titleTextSize = Font::GetFontSize(title->GetFont(), _saveFileName);
    std::shared_ptr<GameObject> layerObj{ Instantiate({{titleLeftPadding + 20.0f + titleTextSize.GetX(), TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
    auto layerTxt = layerObj->AddComponent<Ui::Text>(SPRITE_CATEGORY[_layerIndexTopBar], "goblin", TITLE_FONT_SIZE, Rendering::Color{ 255, 255, 255, 255 });

    std::unordered_map<std::string, SpriteData*> sprites = ResourceManager::GetSprites(SPRITE_CATEGORY);
    std::unordered_map<std::string, std::vector<std::string>> categorySprites;
    
    for (const auto& pair : sprites) 
    {
        const std::string& key = pair.first;
        const std::string& category = pair.second->category;
        categorySprites[category].push_back(key);
    }

    for (int i = 0; i < maxOptionPerRow; i++)
    {
        auto& optionTile = _optionTiles.emplace_back(Instantiate(
        {
            { -SCALE_IN_UI_BAR * 2, -SCALE_IN_UI_BAR * 2},
            0.0f, 
            {SCALE_IN_UI_BAR, SCALE_IN_UI_BAR} 
        }));

        optionTile->AddComponent<Ui::Image>("default_texture");
        optionTile->AddComponent<BrushSprite>("default_texture", &_brush->GetComponent<SnapToGridBrush>());
    }

    auto lambdaChangeSprite = [this, categorySprites, maxOptionPerRow, layerTxt](int wheelDirection) 
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