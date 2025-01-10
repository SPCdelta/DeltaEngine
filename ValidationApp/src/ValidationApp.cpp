#include "ValidationApp.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/InputTestScene.hpp"
#include "Scenes/FileScene.hpp"
#include "Scenes/PhysicsScene.hpp"
#include "Scenes/SwitchTestScene.hpp"
#include "Scenes/LayerScene.hpp"
#include "Scenes/DevScene.hpp"
#include "Scenes/LevelEditor.hpp"
#include "Scenes/ParticleScene.hpp"
#include "Scenes/LevelEditorLevelChose.hpp"
#include "Scenes/SpawnerScene.hpp"
#include "Scenes/WeaponSelectionScene.hpp"

// Game Scenes
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/LevelSelectScene.hpp"
#include "Scenes/LevelScene.hpp"
#include "Scenes/LevelEditorMenuScene.hpp"

ValidationApp::ValidationApp()
	: Application(64)
{

	LoadAssets();

	// Register Scenes (Debug)
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	RegisterScene<FileScene>("FileScene");
	RegisterScene<PhysicsScene>("PhysicsScene");
	RegisterScene<Scene1>("Scene1");
	RegisterScene<Scene2>("Scene2");
	RegisterScene<DevScene>("DevScene");
	RegisterScene<LayerScene>("LayerScene");
	RegisterScene<LevelEditor>("LevelEditor");
	RegisterScene<ParticleScene>("ParticleScene");
	RegisterScene<SpawnerScene>("SpawnerScene");
	RegisterScene<WeaponSelectionScene>("WeaponSelectionScene");

	// Register Scenes (Game)
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<LevelSelectScene>("LevelSelectScene");
	RegisterScene<LevelScene>("LevelScene");
	RegisterScene<LevelEditorMenuScene>("LevelEditorMenuScene");

	// Load Desired Scene
	LoadScene("MainMenuScene");

	// Start Application
	Run();
}


void ValidationApp::LoadAssets()
{
	// Maps
	float scale = 32.0f;

	SpriteMap gamefloormap{
		"Assets\\Textures\\floor_map.png",
		{

			{"ice", {scale * 0, scale * 0}, {scale, scale}},
			{"mud", {scale * 1, scale * 0}, {scale, scale}},
			{"stone_wall", {scale * 0, scale * 1}, {scale, scale}},
			{"stone_floor", {scale * 1, scale * 1}, {scale, scale}},
		}
	};

	SpriteMap floormap
	{
		"Assets\\Textures\\Tiles\\floor.png",
		{
			{"Sandstone_floor_0",	{scale * 8, scale * 0}, {scale*(8 + 1), scale*(0 + 1)}},
			{"Sandstone_floor_1",	{scale * 9, scale * 0}, {scale*(9 + 1), scale*(0 + 1)}},
			{"Sandstone_floor_2",	{scale * 0, scale * 1}, {scale*(0 + 1), scale*(1 + 1)}},
			{"Sandstone_floor_3",	{scale * 1, scale * 1}, {scale*(1 + 1), scale*(1 + 1)}},
			{"Sandstone_floor_4",	{scale * 2, scale * 1}, {scale*(2 + 1), scale*(1 + 1)}},
			{"Sandstone_floor_5",	{scale * 3, scale * 1}, {scale*(3 + 1), scale*(1 + 1)}},
			{"Sandstone_floor_6",	{scale * 4, scale * 1}, {scale*(4 + 1), scale*(1 + 1)}},
			{"Sandstone_floor_7",	{scale * 5, scale * 1}, {scale*(5 + 1), scale*(1 + 1)}},
			{"Sandstone_floor_8",	{scale * 6, scale * 1}, {scale*(6 + 1), scale*(1 + 1)}},
			{"Sandstone_floor_9",	{scale * 7, scale * 1}, {scale*(7 + 1), scale*(1 + 1)}},
		},
		"floor_tiles"
	};

	SpriteMap wallTiles
	{
		"Assets\\Textures\\Tiles\\floor.png",
		{

			{"tomb_0_old",			{scale * 0, scale * 0}, {scale * (0 + 1), scale * (0 + 1)}},
			{"tomb_0_new",			{scale * 1, scale * 0}, {scale * (1 + 1), scale * (0 + 1)}},
			{"tomb_1_old",			{scale * 2, scale * 0}, {scale * (2 + 1), scale * (0 + 1)}},
			{"tomb_1_new",			{scale * 3, scale * 0}, {scale * (3 + 1), scale * (0 + 1)}},
			{"tomb_2_old",			{scale * 4, scale * 0}, {scale * (4 + 1), scale * (0 + 1)}},
			{"tomb_2_new",			{scale * 5, scale * 0}, {scale * (5 + 1), scale * (0 + 1)}},
			{"tomb_3_old",			{scale * 6, scale * 0}, {scale * (6 + 1), scale * (0 + 1)}},
			{"tomb_3_new",			{scale * 7, scale * 0}, {scale * (7 + 1), scale * (0 + 1)}},
			{"rect_gray_0_old",		{scale * 8, scale * 1}, {scale * (8 + 1), scale * (1 + 1)}},
			{"rect_gray_0_new",		{scale * 9, scale * 1}, {scale * (9 + 1), scale * (1 + 1)}},
		},
		"wall_tiles"
	};

	SpriteMap particlesMap
	{
		"Assets\\Textures\\Particles\\particles.png",
		{
			{ "particle_big", { 0, 0 }, { 5, 5 } },
			{ "particle_medium_1", { 5, 0 }, { 8, 3 } },
			{ "particle_medium_2", { 8, 0 }, { 11, 3 } },
			{ "particle_small", { 11, 0 }, { 13, 2 } },
			{ "particle_tiny", { 13, 0 }, { 14, 1 } }
		},
		"particles_map", 
	};

	SpriteMap exit
	{
		"Assets\\Textures\\Tiles\\doors.png",
		{
			{ "level_exit", {scale * 2, scale * 5}, {scale * (2 + 1), scale * (5 + 1)}},
		},
		"level_exit",
	};

	SpriteMap spawners
	{
		"Assets\\Textures\\Tiles\\Walls\\wall.png",
		{
			{ "spawner_1", {scale * 1, scale * 1}, {scale * (1 + 1), scale * (1 + 1)}},
		},
		"enemy_spawners",
	};

	ResourceManager::AddSprite("layerPlayer", "Assets\\Textures\\Player\\player_no_weapon.png");
	ResourceManager::AddSprite("player", "Assets\\Textures\\player.png");
	ResourceManager::AddSprite("gray_rect", "Assets\\Textures\\Rect.png");
	ResourceManager::AddSprite("cyanPotion", "Assets\\Textures\\Items\\potions\\cyan.png");
	ResourceManager::AddSprite("potion_effervescent", "Assets\\Textures\\Items\\potions\\potion_effervescent.png");
	ResourceManager::AddSprite("spritesheet", "Assets\\Textures\\spritesheet.png");
	ResourceManager::AddSprite("spritesheet2", "Assets\\Textures\\spritesheet2.png");
	ResourceManager::AddSprite("spritesheet3", "Assets\\Textures\\spritesheet3.png");
	ResourceManager::AddSprite("square", "Assets\\Textures\\square.png", "enemy");
	ResourceManager::AddSprite("default_texture", "Assets\\Textures\\default_texture.png");

	// Weapons
	ResourceManager::AddSprite("boomerang", "Assets\\Textures\\Weapons\\boomerang.png");
	ResourceManager::AddSprite("bullet", "Assets\\Textures\\Weapons\\bullet.png");
	ResourceManager::AddSprite("gun", "Assets\\Textures\\Weapons\\gun.png");
	ResourceManager::AddSprite("arrow", "Assets\\Textures\\Weapons\\arrow.png");
	ResourceManager::AddSprite("bow", "Assets\\Textures\\Weapons\\bow.png");

	// Enemies
	ResourceManager::AddSprite("goblin", "Assets\\Textures\\Enemies\\goblin_attacking.png");
	ResourceManager::AddSprite("slime", "Assets\\Textures\\Enemies\\slime_walking.png");
	ResourceManager::AddSprite("boss", "Assets\\Textures\\Enemies\\slime_boss.png");
	ResourceManager::AddSprite("skeleton", "Assets\\Textures\\Enemies\\skeleton_walking_bow.png");

	// UI
	ResourceManager::AddSprite("main_menu_bg", "Assets\\Textures\\UI\\Background\\main_menu_bg.png");
	ResourceManager::AddSprite("scroll", "Assets\\Textures\\UI\\Buttons\\scroll.png");
	ResourceManager::AddSprite("scroll2", "Assets\\Textures\\UI\\Buttons\\scroll2.png");
	ResourceManager::AddSprite("scroll3", "Assets\\Textures\\UI\\Buttons\\scroll3.png");
	ResourceManager::AddSprite("window_frame", "Assets\\Textures\\UI\\window_frame.png");
	ResourceManager::AddSprite("weapon_frame", "Assets\\Textures\\UI\\weapon_frame.png");

	// HUD
	ResourceManager::AddSprite("bar", "Assets\\Textures\\HUD\\bar.png");
	ResourceManager::AddSprite("bar_frame", "Assets\\Textures\\HUD\\bar_frame.png");
	ResourceManager::AddSprite("coin", "Assets\\Textures\\Items\\coin.png");
	ResourceManager::AddSprite("health_bar", "Assets\\Textures\\HUD\\health_bar.png");
	ResourceManager::AddSprite("shield_bar", "Assets\\Textures\\HUD\\shield_bar.png");
	ResourceManager::AddSprite("hotbar_slot", "Assets\\Textures\\HUD\\hotbar_slot.png");
	ResourceManager::AddSprite("active_slot", "Assets\\Textures\\HUD\\active_slot.png");

	// Fonts
	ResourceManager::AddFont("alucrads","Assets\\Fonts\\alucrads.otf");
	ResourceManager::AddFont("knight","Assets\\Fonts\\knight_warrior.otf");
	ResourceManager::AddFont("goblin","Assets\\Fonts\\a_goblin_appears.ttf");

	// Audio
	ResourceManager::AddAudio("taking_damage", "Assets\\Audio\\SFX\\Taking_damage.mp3");
	ResourceManager::AddAudio("death", "Assets\\Audio\\SFX\\Death.mp3");
	ResourceManager::AddAudio("bow_shoot", "Assets\\Audio\\SFX\\Bow_shoot.mp3");
	ResourceManager::AddAudio("boomerang_throw", "Assets\\Audio\\SFX\\boomerang.mp3");

	ResourceManager::AddAudio("goblin_death", "Assets\\Audio\\SFX\\Goblin_death_1.mp3");
	ResourceManager::AddAudio("skeleton_death", "Assets\\Audio\\SFX\\Skeleton_death.mp3");
	ResourceManager::AddAudio("slime_death", "Assets\\Audio\\SFX\\Slime_death.mp3");

	ResourceManager::AddAudio("button_1_click", "Assets\\Audio\\SFX\\Button_1.mp3");

	ResourceManager::AddAudio("boss_music", "Assets\\Audio\\Music\\Boss_music_1.mp3");
	ResourceManager::AddAudio("intro_theme", "Assets\\Audio\\Music\\Intro_Theme.mp3");
	ResourceManager::AddAudio("menu", "Assets\\Audio\\Music\\Menu_music.mp3");
}
