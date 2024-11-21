#include "ValidationApp.hpp"

ValidationApp::ValidationApp() 
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");

	// Load Desired Scene
	LoadScene("MainMenuScene");

	// Start Application
	Run();
}
