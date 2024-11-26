#include "ValidationApp.hpp"

#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/InputTestScene.hpp"
#include "Scenes/FileManagementScene.hpp"

ValidationApp::ValidationApp()
	: Application(100)
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	RegisterScene<FileManagementScene>("FileManagement");
	//RegisterScene<PhysicsScene>("PhysicsScene");

	// Load Desired Scene
	LoadScene("FileManagement");

	// Start Application
	Run();
}
