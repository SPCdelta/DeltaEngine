#include "ValidationApp.hpp"

#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/InputTestScene.hpp"
#include "Scenes/FileScene.hpp"
#include "Scenes/PhysicsScene.hpp"
#include "Scenes/SwitchTestScene.hpp"
#include "Scenes/LayerScene.hpp"
#include "Scenes/DevScene.hpp"

ValidationApp::ValidationApp()
	: Application(32)
{
	// Load Assets
	LoadAssets();

	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	RegisterScene<FileScene>("FileScene");
	RegisterScene<PhysicsScene>("PhysicsScene");
	RegisterScene<Scene1>("Scene1");
	RegisterScene<Scene2>("Scene2");
	RegisterScene<DevScene>("DevScene");
	RegisterScene<LayerScene>("LayerScene");

	// Load Desired Scene
	LoadScene("MainMenuScene");

	// Start Application
	Run();
}

void ValidationApp::LoadAssets()
{
	// Maps
	SpriteMap floormap
	{
		"floor_map",
		"Assets\\Textures\\floor_map.png",
		{
			{
				"ice",
				{ 0.0f, 0.0f },
				{ 32.0f, 32.0f }
			},
			{
				"mud",
				{ 32.0f, 0.0f },
				{ 64.0f, 32.0f }
			},
			{
				"stone_floor",
				{ 0.0f, 32.0f }, 
				{ 32.0f, 64.0f }
			},
		}
	};

	SpriteMap wallmap
	{
		"wall_map",
		"Assets\\Textures\\wall_map.png",
		{
			{
				"stone_wall",
				{ 0.0f, 0.0f },
				{ 32.0f, 32.0f }
			}
		}
	};

	// Single
	ResourceManager::Add("player", "Assets\\Textures\\player.png");
	ResourceManager::Add("spritesheet", "Assets\\Textures\\spritesheet.png");
	ResourceManager::Add("spritesheet2", "Assets\\Textures\\spritesheet2.png");
	ResourceManager::Add("spritesheet3", "Assets\\Textures\\spritesheet3.png");
	ResourceManager::Add("square", "Assets\\Textures\\square.png");
	ResourceManager::Add("default_texture", "Assets\\Textures\\default_texture.png");
	ResourceManager::Add("menu_button", "Assets\\Textures\\UI\\Buttons\\menu_button.png");
	ResourceManager::Add("boomerang", "Assets\\Textures\\Weapons\\boomerang.png");
	ResourceManager::Add("main_menu_bg", "Assets\\Textures\\UI\\Background\\main_menu_bg.png");
}
