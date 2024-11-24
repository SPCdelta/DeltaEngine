#include "ValidationApp.hpp"

ValidationApp::ValidationApp() 
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
