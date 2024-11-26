#include "ValidationApp.hpp"

#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/InputTestScene.hpp"
#include "Scenes/FileScene.hpp"
#include "Scenes/PhysicsScene.hpp"
#include "Scenes/SwitchTestScene.hpp"


ValidationApp::ValidationApp()
	: Application(64)
{
	// Register Scenes
	RegisterScene<MainMenuScene>("MainMenuScene");
	RegisterScene<GameScene>("GameScene");
	RegisterScene<InputTestScene>("InputTest");
	RegisterScene<FileScene>("FileScene");
	RegisterScene<PhysicsScene>("PhysicsScene");
	RegisterScene<Scene1>("Scene1");
	RegisterScene<Scene2>("Scene2");

	// Load Desired Scene
	LoadScene("FileScene");

	// Start Application
	Run();

	// TODO when you close a scene, save to file
	// TODO when you open a scene, load from file
	// TODO save to file when specific method is called
	// TODO sprite memory leak
}
