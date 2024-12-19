#pragma once

#include "Engine/Delta.hpp"
#include "Engine/UI/Scrollable.hpp"

#include "../Scripts/MouseFollowBehaviour.hpp"
#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"

// Brushes
#include "Engine/UI/Brush/EraserBrush.hpp"

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
    LevelEditor(const std::string& sceneName) : Scene(sceneName) 
    {
        _saveFileName = "level-1";

        _saveFilePath = LEVEL_PATH + _saveFileName + ".json";

        auto allLayers = LayerHelper::GetAllLayer();
    }

    ~LevelEditor()
    {
        for (Brush* brush : _brushes)
        {
			delete brush;
        }
		_brushes.clear();
    }

    void OnStart() override
    {
        ViewportData& viewport = GetWindow()->GetViewport();
        const int windowWidth = viewport.width;
        const int windowHeight = viewport.height;

        const float topBarHeight = PADDING_TOP + SCALE_IN_UI_BAR + 10.0f;
        const float titleLeftPadding = windowWidth / 2 - TITLE_WIDTH / 2;

        const float rightBarStart = windowWidth - RIGHT_BAR_WIDTH;

        _screenPort = { {0.0f, topBarHeight}, 0.0f, {static_cast<float>(windowWidth), windowHeight - topBarHeight} };

        InitLevelEditor(_saveFileName);

        UIBackButtonAndBinding(rightBarStart);
        UISaveButtonAndBinding(rightBarStart);
        BindLayerChangerToMouseWheel(titleLeftPadding, topBarHeight, windowWidth, windowHeight);
        UITopBarAndBinding(windowWidth, titleLeftPadding, topBarHeight);
        BindCamara();
        CreateBrushes();
    }

    void InitLevelEditor(const std::string& level)
    {
        // Load Level
        {
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
                        CreateTile(tile["sprite"]["name"], tile["sprite"]["name"], TransformDTO::JsonToTransform(tile));
                        _tiles.back()->SetTag(SPRITE_CATEGORY[0]);
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
                    CreateTile(player["sprite"]["name"], player["sprite"]["name"], TransformDTO::JsonToTransform(player));
                    _tiles.back()->SetTag(SPRITE_CATEGORY[1]);
                    //_tilesPerLayer[_layer].back()->GetComponent<SnapToGridBrush>().SetDraggeble(false);
                }
            }
		}
    }

    void CreateBrushes()
    {
		//_brushes.push_back(new SnapToGridBrush());
        EraserBrush* eraser = new EraserBrush(Instantiate().get(), 
            [this](Brush* brush)
            {
                auto& vector = _tiles;
				std::string spriteName = brush->GetSprite()->GetSprite();
				const Vector2& position = brush->GetPosition();

                auto it = std::find_if(vector.begin(), vector.end(), 
                    [this, position, spriteName](std::shared_ptr<GameObject>& e)
                    {
            		    if (e->transform->position == position)
                        {
							e->Destroy(e);
                            return true;
            		    }
                        return false;
                    }
                );
            });

		SnapToGridBrush* regular = new SnapToGridBrush(Instantiate().get(), 
            [this](Brush* brush)
            {
                auto& vector = _tiles;
				std::string spriteName = brush->GetSprite()->GetSprite();
				const Vector2& position = brush->GetPosition();

                auto it = std::find_if(vector.begin(), vector.end(), 
                    [this, position, spriteName](std::shared_ptr<GameObject>& e)
                    {
            		    if (e->transform->position == position)
                        {
            			    e->GetComponent<Sprite>().SetSprite(spriteName);
                            return true;
            		    }
                        return false;
                    }
                );

                if (it == vector.end())
				{
					CreateTile(spriteName, brush->GetSprite()->GetSpriteData()->category);
				}
            }, _screenPort
        );
		_brushes.push_back(eraser);
		_brushes.push_back(regular);

        for (Brush* brush : _brushes)
        {
			_inputListeners.Add(InputManager::onKeyPressed(brush->Shortcut(), 
                [this, brush](Input& e) 
                { 
                    // Disable Others
                    for (Brush* other : _brushes)
                    {
						if (brush == other)
							continue;

                        other->Disable();
                    }

                    // Toggle Selected
					brush->Toggle();
                    _selectedBrush = brush;
                })
            );
        }

		_selectedBrush = regular;
		_selectedBrush->Enable();
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
                tileJson["sprite"]["name"] = tile->GetComponent<Sprite>().GetSprite();
                tileJson["tag"] = StringUtils::Split(tileJson["sprite"]["name"], '_')[0];
                tileJson["sprite"]["layer"] = tile->GetLayer();
                tileCounter++;

            } else if (tile->GetTag() == SPRITE_CATEGORY[1]){ //player
                auto& tileJson = tilesJson["player"];
                TransformDTO::ToJson(tileJson, tile->GetComponent<Transform>());
                tileJson["sprite"]["name"] = tile->GetComponent<Sprite>().GetSprite();
                tileJson["tag"] = StringUtils::Split(tileJson["sprite"]["name"], '_')[0];
                tileJson["sprite"]["layer"] = tile->GetLayer();
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
    void CreateTile(const std::string& spriteName, const std::string& category, Transform transform) {
        _tiles.emplace_back(Instantiate(transform));
        CreateTile(spriteName, category, false);

    }

    void CreateTile(const std::string& spriteName, const std::string& category, bool mousePos = true)
    {
        if (mousePos) {
            auto mousePos = InputManager::GetMousePosition();
            _tiles.emplace_back(Instantiate({ camera->ToWorldGrid(mousePos), 0.0f, {1.0f, 1.0f} }));
        }

        auto& tile = _tiles.back();
        tile->SetTag(category);

        auto sprite = tile->AddComponent<Sprite>(spriteName);
        sprite->SetLayer(_layer);
    }


    //Input Binding
    void BindLayerChangerToMouseWheel(float titleLeftPadding, float topBarHeight, int windowWidth, int windowHeight)
    {
        std::shared_ptr<GameObject> layerTxt{ Instantiate({{titleLeftPadding + 160.0f, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto layer = layerTxt->AddComponent<Ui::Text>("Layer: " + LayerHelper::GetString(_layer), "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        layer->SetBackground({ 255, 255, 255, 255 });

        std::shared_ptr<GameObject> worldView{ Instantiate(_screenPort) };
        worldView->AddComponent<Ui::Scrollable>(
            [this, layer](int wheelDirection) {
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
        float speed = 1.0f;
        _inputListeners.Add(InputManager::keyPressed(KEY_D, 
            [this, speed](Input& e) 
            {
                camera->AddToPosition({ speed, 0.0f });
				_selectedBrush->NotifyTransform();
            }
        ));
        _inputListeners.Add(InputManager::keyPressed(KEY_A, 
            [this, speed](Input& e) 
            {
                camera->AddToPosition({ -speed, 0.0f });
                _selectedBrush->NotifyTransform();
            }
        ));
        _inputListeners.Add(InputManager::keyPressed(KEY_S, 
            [this, speed](Input& e) 
            {
                camera->AddToPosition({ 0.0f, -speed });
                _selectedBrush->NotifyTransform();
            }
        ));
        _inputListeners.Add(InputManager::keyPressed(KEY_W, 
            [this, speed](Input& e) 
            {
                camera->AddToPosition({ 0.0f, speed });
                _selectedBrush->NotifyTransform();
            }
        ));
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

    void UITopBarAndBinding(int windowWidth, float titleLeftPadding, float topBarHeight)
    {
        const float imagespace = (SCALE_IN_UI_BAR + PADDING);
        
        const int maxOptionPerRow = static_cast<int>((static_cast<float>(windowWidth) - PADDING_OUT_LEFT_UI * 2 - RIGHT_BAR_WIDTH) / imagespace);
        const float topBarLength = imagespace * maxOptionPerRow;
        
        std::shared_ptr<GameObject> titleTxt{ Instantiate({{titleLeftPadding, TITLE_TOP_PADDING}, 0.0f, {TITLE_WIDTH, TITLE_FONT_SIZE}}) };
        auto title = titleTxt->AddComponent<Ui::Text>("Level: " + _saveFileName, "knight", TITLE_FONT_SIZE, Rendering::Color{ 0, 0, 0, 255 });
        title->SetBackground({ 255, 255, 255, 255 });

        std::unordered_map<std::string, SpriteData*> sprites = ResourceManager::GetSprites(SPRITE_CATEGORY);

        int maxtileIndexOptions = static_cast<int>(sprites.size()) / maxOptionPerRow;

        for (auto& [key, value] : sprites)
        {
            auto& optionTile = _optionTiles.emplace_back(Instantiate({
                    {-SCALE_IN_UI_BAR, -SCALE_IN_UI_BAR},
                    0.0f, {SCALE_IN_UI_BAR, SCALE_IN_UI_BAR} }));


            optionTile->AddComponent<Ui::Image>(key);
			//Ui::Button* button = optionTile->AddComponent<Ui::Button>(optionTile->transformRef.position, optionTile->transformRef.scale);
   //         button->SetOnLeftMouseClick(
   //             [this, key]() 
   //             {
   //                 _selectedBrush->GetSprite()->SetSprite(key);
   //             }, "level_editor"
   //         );

            _inputListeners.Add(InputManager::onMouseButtonDown(MouseButton::Left,
			    [this, optionTile, key](Input& e)
			    {
				    if (!Math::MathUtils::IsVector2WithinRect({ e.mouseX, e.mouseY }, optionTile->transformRef.position, optionTile->transformRef.scale))
					    return;

				    _selectedBrush->GetSprite()->SetSprite(key);

			    }, "level_editor"
		    ));
            //optionTile->AddComponent<BrushSprite>(key, &_brush->GetComponent<SnapToGridBrush>());
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
            for (auto& pair = startIt; pair != sprites.end() && index < maxOptionPerRow; ++pair) {

                auto& tileoption = _optionTiles.at(maxOptionPerRow * _tileIndexOptions + index);

                tileoption->transform->position.Set({ SCALE_IN_UI_BAR * index + PADDING * index + PADDING_OUT_LEFT_UI, PADDING_TOP });

                index++;
            }

        };
        lambdaChangeSprite(0);


        std::shared_ptr<GameObject> TopBar{ Instantiate({{0.0f, 0.0f}, 0.0f, {static_cast<float>(windowWidth), topBarHeight}}) };
        TopBar->AddComponent<Ui::Scrollable>(lambdaChangeSprite);

    }

private:
    
    void HiddeOptionTiles(){
        for (auto& option : _optionTiles)
        {
            option->transform->position.Set({ -SCALE_IN_UI_BAR, -SCALE_IN_UI_BAR });
        }
    }

    InputHandler _inputListeners;
    Transform _screenPort;

    std::string _saveFilePath;
    std::string _saveFileName;

    std::vector<std::shared_ptr<GameObject>> _tiles;
    std::vector<std::shared_ptr<GameObject>> _optionTiles;
    int _tileIndexOptions = 0;

    // Brushes
    Brush* _selectedBrush = nullptr;
	std::vector<Brush*> _brushes{};


    Layer _layer = Layer::Default;

};
