#include "ValidationApp.hpp"

#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/InputTestScene.hpp"


ValidationApp::ValidationApp()
	: Application(32)
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	//RegisterScene<PhysicsScene>("PhysicsScene");

	// Load Desired Scene
	LoadScene("GameScene");

	// Start Application
	Run();
}
