#include "ValidationApp.hpp"

#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/InputTestScene.hpp"
#include "Scenes/PhysicsScene.hpp"


ValidationApp::ValidationApp()
	: Application(100)
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	RegisterScene<PhysicsScene>("PhysicsScene");

	// Load Desired Scene
	LoadScene("PhysicsScene");

	// Start Application
	Run();
}
