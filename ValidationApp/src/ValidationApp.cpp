#include "ValidationApp.hpp"

ValidationApp::ValidationApp() 
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");

	// Load Desired Scene
	LoadScene("GameScene");

	// Start Application
	Run();
}
