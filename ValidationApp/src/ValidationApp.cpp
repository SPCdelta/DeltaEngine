#include "ValidationApp.hpp"

ValidationApp::ValidationApp()
	: Application(64)
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<PhysicsScene>("PhysicsScene");

	// Load Desired Scene
	LoadScene("PhysicsScene");

	// Start Application
	Run();
}
