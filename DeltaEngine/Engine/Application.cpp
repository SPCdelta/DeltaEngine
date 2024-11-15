#include "Application.hpp"

bool Application::_isRunning = true;

Application::Application() : _window("Meow!", 1280, 720)
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

	_window.SetViewportSize(400, 400);
	_window.SetViewportPos(100, 50);
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

		Rendering::GetWindowSize(_window, &_viewportData.width, &_viewportData.height);

		//TODO waar is de inputmanager update ???
		
		// if (_windowEvent.type == SDL_KEYDOWN)
		// {
		// 	auto keyPresSim =
		// 		new IKeyListener(SDL_GetKeyName(_windowEvent.key.keysym.sym));
		// 	InputManager::GetInstance().setKeyDown(*keyPresSim);
		// }


		GetDeltaTime();

		// Update Window
		_window.Update();		

		// Input
		Input(_dt); //TODO wat is dit?

		// Scene UpdateLoop
		std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
		currentScene->Update();

		//Input(_dt);
		//_debugSystem->Update();

		//// Update
		////b2World_Step(Singleton::get_instance()._worldId, Temp::TIME_STEP, Temp::SUB_STEP_COUNT);
		//_updateSystem->Update();
		////_physicsSystem->Update();

		//// Render
		////_renderSystem->Update();
		////_fontRenderSystem->Update();
		//Rendering::RenderPresent(_window.GetRenderer());

		////ShowFpsInWindowTitleBar();

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

void Application::GetDeltaTime()
{

}

void Application::ShowFpsInWindowTitleBar()
{

}
