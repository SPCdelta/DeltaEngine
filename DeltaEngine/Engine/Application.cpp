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

	// TODO #2 move into scene
	// GameObject* gameObject = new GameObject(_reg, _physicsWorld, Transform({10.0f, 10.0f}, 0.0f, {64.0f, 64.0f}));
	// gameObject->AddComponent<A>();
	// gameObject->AddComponent<B>();
	// gameObject->AddComponent<TempBehaviour>();
	// gameObject->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");

	// GameObject* fo1 = new GameObject(_reg, _physicsWorld, Transform({ 600.0f, 100.0f }, 0.0f, { 64.0f, 64.0f }));
	// fo1->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");
	// fo1->AddComponent<Physics::BoxCollider>();
	// fo1->AddComponent<Physics::Rigidbody>();
	// fo1->AddComponent<PhysicsBehaviour>();

	// GameObject* fo2 = new GameObject(_reg, _physicsWorld, Transform({ 600.0f, 500.0f }, 0.0f, { 64.0f, 64.0f }));
	// fo2->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");
	// fo2->AddComponent<Physics::BoxCollider>();

	// TODO #2 _renderSystem = _reg.CreateSystem<RenderSystem, Transform, Sprite>();

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

		// Internal Input
		if (_windowEvent.type == Rendering::KEYDOWN)
		{
			//InputManager::GetInstance().SetKeyState(_windowEvent.key.keysym.scancode, 1.0f);

		}
		else if (_windowEvent.type == Rendering::KEYUP)
		{
			//InputManager::GetInstance().SetKeyState(_windowEvent.key.keysym.scancode, 0.0f);
		}

		GetDeltaTime();

		// Update Window
		_window.Update();		

		// Input
		Input(_dt);

		// Scene UpdateLoop
		std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
		currentScene->Update();
		// TODO #2 _physicsSystem->Update();

		ShowFpsInWindowTitleBar();

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
