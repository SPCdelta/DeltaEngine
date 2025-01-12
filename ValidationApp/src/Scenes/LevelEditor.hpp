#pragma once

#include "Engine/Delta.hpp"

#include "Engine/UI/Scrollable.hpp"
#include "../Scripts/PlayerBehaviour.hpp"

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

    const std::vector<std::string> SPRITE_CATEGORY = 
    {
		"floor_tiles",	  
        "wall_tiles", 
        "player",
		"enemy_spawners", 
        "level_exit", 
        "potions"
    };

	const std::map<std::string, Layer> LAYER_MAP = 
    {
		{"floor_tiles", Layer::Floor},	   
        {"wall_tiles", Layer::Wall},
		{"player", Layer::Player},		   
        {"enemy_spawners", Layer::Player},
		{"level_exit", Layer::Foreground}, 
        {"potions", Layer::Items}
    };

    // Constructor
	LevelEditor(const std::string& sceneName);

    void OnStart() override;
    void InitLevelEditor();

    //File handling
    void CreateTilesFromJson(Json::json& loadTiles, const std::string& jsonarray);
	void SaveLevel();
    void MakeSaveFilePath();

    void CreateTile(const std::string& spriteName, const std::string& category);

    void BindCamera();

    //UI Input Binding
	void UIBackButtonAndBinding(const float rightBarStart);
    void UISaveButtonAndBinding(const float rightBarStart);
    void UITopBarAndBinding(int windowWidth, float titleLeftPadding, float topBarHeight);

    int CalculateSpritesInrow(std::unordered_map<std::string, std::vector<std::string>> categorySprites, int maxVisibleSprites);

    std::vector<std::string> GetVisibleSprites(std::unordered_map<std::string, std::vector<std::string>> categorySprites, int maxVisibleSprites, int direction);

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
