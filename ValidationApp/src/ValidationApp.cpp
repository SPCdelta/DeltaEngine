#include "ValidationApp.hpp"

ValidationApp::ValidationApp()
	: Application(32)
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<PhysicsScene>("PhysicsScene");

	// Load Desired Scene
	LoadScene("GameScene");

	// Start Application
	Run();
}
