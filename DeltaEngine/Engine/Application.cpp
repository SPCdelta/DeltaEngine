#include "Application.hpp"

bool Application::_isRunning = true;

Application::Application(int unitPixelSize)
	: _window("Meow!", 1280, 720)
{
	// Init SDL2
	if (Rendering::Initialize(Rendering::INIT_VIDEO | Rendering::INIT_AUDIO) < 0)
	{
		std::cerr << "Failed to initialize the SDL2 library" << std::endl;
	}

	// Init SDL2 image 
	if (!(Rendering::InitializeImage(Rendering::INIT_PNG) & Rendering::INIT_PNG))
	{
		std::cerr << "Failed to initialize the SDL2_image library" << std::endl;
	}

	// Init SDL2_ttf
	if (TTF_Init() < 0)
	{
		std::cerr << "Failed to initialize the SDL2_ttf library" << std::endl;
	}

	ChangeScene.Register([this](const std::string& sceneName) 
		{ 
			LoadScene(sceneName);
		});

	//_window.SetViewportSize(400, 400);
	//_window.SetViewportPos(100, 50);
	_window.SetUnitPixelSize(unitPixelSize);
}

Application::~Application()
{
	Stop();
}

void Application::Run()
{
	while (!_window.ShouldWindowClose())
	{
		Rendering::PollEvent(_windowEvent);

		if (!Application::_isRunning || _windowEvent.type == Rendering::QUIT)
		{
			Stop();
			break;
		}

		_inputFacade.onInputEvent(_windowEvent);
		InputManager::GetInstance().executeInputEvents();

		// Clear Screen
		Rendering::RenderClear(_window.GetRenderer());



		// Update Window
		_window.Update();	

		// Input
		Input(_dt);

		// Scene UpdateLoop
		std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
		currentScene->Update();

		// Draw
		Rendering::RenderPresent(_window.GetRenderer());

		// Framerate
		Rendering::Delay(1000 / 60);
	}
}

void Application::LoadScene(const std::string& sceneName)
{
	_sceneManager.Load(sceneName);
	std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
	currentScene->_changeSceneEvent.Register([this](const std::string& name) { ChangeScene.Dispatch(name); });
	currentScene->SetWindow(_window);
	currentScene->Start();
}

//Texture* Application::LoadTexture(const char* path)
//{
//	SDL_Texture* texture{ IMG_LoadTexture(_window.GetRenderer(), path) };
//	return texture;
//}
//
//Font* Application::LoadFont(const char* path, int fontSize)
//{
//	TTF_Font* font = TTF_OpenFont(path, fontSize);
//	return font;
//}

