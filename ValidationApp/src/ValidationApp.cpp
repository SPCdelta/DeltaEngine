#include "ValidationApp.hpp"

#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/InputTestScene.hpp"
#include "Scenes/PhysicsScene.hpp"
#include "Scenes/SwitchTestScene.hpp"


ValidationApp::ValidationApp()
	: Application(64)
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	RegisterScene<PhysicsScene>("PhysicsScene");
	RegisterScene<Scene1>("Scene1");
	RegisterScene<Scene2>("Scene2");

	// Load Desired Scene
	LoadScene("PhysicsScene");

	// Start Application
	Run();
}
