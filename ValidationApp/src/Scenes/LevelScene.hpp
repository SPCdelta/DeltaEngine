#pragma once

#include <Engine/Delta.hpp>

#include "../Scripts/PlayerBehaviour.hpp"
#include "../Views/HUDView.hpp"

struct LevelSceneData
{
	std::string name;
};

class LevelScene : public Scene
{
public:
	static constexpr auto FloorTilesName = "floor_tiles";
	static constexpr auto WallTilesName = "wall_tiles";
	static constexpr auto PlayerName = "player";
	static constexpr auto EnemySpawnersName = "enemy_spawners";
	static constexpr auto LevelExitName = "level_exit";

	LevelScene(const std::string& name) : Scene(name) {}

	void OnStart() override;

private:
	bool LoadLevel(const std::string& levelName);

	std::unique_ptr<HUDView> _hud;
};