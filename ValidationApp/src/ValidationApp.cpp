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
	LoadScene("GameScene");

	// Start Application
	Run();

	// TODO when you close a scene, save to file
	// TODO when you open a scene, load from file
	// TODO save to file when specific method is called
	// TODO sprite memory leak
}
