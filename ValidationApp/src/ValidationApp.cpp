#include "ValidationApp.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/InputTestScene.hpp"
#include "Scenes/FileScene.hpp"
#include "Scenes/PhysicsScene.hpp"
#include "Scenes/SwitchTestScene.hpp"
#include "Scenes/UIScene.hpp"
#include "Scenes/LayerScene.hpp"
#include "Scenes/LevelEditor.hpp"

ValidationApp::ValidationApp()
	: Application(32)
{

	LoadAssets();

	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	RegisterScene<FileScene>("FileScene");
	RegisterScene<PhysicsScene>("PhysicsScene");
	RegisterScene<Scene1>("Scene1");
	RegisterScene<Scene2>("Scene2");
	RegisterScene<UIScene>("UIScene");
	RegisterScene<LayerScene>("LayerScene");
	RegisterScene<LevelEditor>("LevelEditor");

	// Load Desired Scene
	LoadScene("LevelEditor");


	// Start Application
	Run();
}


void ValidationApp::LoadAssets()
{
	// Maps
	float scale = 32.0f;
	SpriteMap floormap
	{
		"floor_map",
		"Assets\\Textures\\Tiles\\floor.png",
		{

			{"tomb_0_old",			{scale * 0, scale * 0}, {scale*(0 + 1), scale*(0 + 1)}},
			{"tomb_0_new",			{scale * 1, scale * 0}, {scale*(1 + 1), scale*(0 + 1)}},
			{"tomb_1_old",			{scale * 2, scale * 0}, {scale*(2 + 1), scale*(0 + 1)}},
			{"tomb_1_new",			{scale * 3, scale * 0}, {scale*(3 + 1), scale*(0 + 1)}},
			{"tomb_2_old",			{scale * 4, scale * 0}, {scale*(4 + 1), scale*(0 + 1)}},
			{"tomb_2_new",			{scale * 5, scale * 0}, {scale*(5 + 1), scale*(0 + 1)}},
			{"tomb_3_old",			{scale * 6, scale * 0}, {scale*(6 + 1), scale*(0 + 1)}},
			{"tomb_3_new",			{scale * 7, scale * 0}, {scale*(7 + 1), scale*(0 + 1)}},
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
			{"rect_gray_0_old",		{scale * 8, scale * 1}, {scale*(8 + 1), scale*(1 + 1)}},
			{"rect_gray_0_new",		{scale * 9, scale * 1}, {scale*(9 + 1), scale*(1 + 1)}},
		}

	};

	ResourceManager::AddSprite("player", "Assets\\Textures\\player.png");
	ResourceManager::AddSprite("gray_rect", "Assets\\Textures\\Rect.png");
	ResourceManager::AddSprite("spritesheet", "Assets\\Textures\\spritesheet.png");
	ResourceManager::AddSprite("spritesheet2", "Assets\\Textures\\spritesheet2.png");
	ResourceManager::AddSprite("spritesheet3", "Assets\\Textures\\spritesheet3.png");
	ResourceManager::AddSprite("square", "Assets\\Textures\\square.png");
	ResourceManager::AddSprite("default_texture", "Assets\\Textures\\default_texture.png");
	ResourceManager::AddSprite("boomerang", "Assets\\Textures\\Weapons\\boomerang.png");
	ResourceManager::AddFont("knight","Assets\\Fonts\\knight_warrior.otf");
}
