#include "Application.hpp"
#include "Temp/TempAudio.hpp"
#include "Audio/SFXSource.hpp"

bool Application::_isRunning = true;

Application::Application()
	: _window("Meow!", 1280, 720), _audioFacade(Audio::AudioFacade{})
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

	GameObject* gameObject = new GameObject(_reg, _audioFacade, Transform({10.0f, 10.0f}, 0.0f, {64.0f, 64.0f}));
	gameObject->AddComponent<A>();
	gameObject->AddComponent<B>();
	gameObject->AddComponent<TempBehaviour>();
	gameObject->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");
	gameObject->AddComponent<Audio::SFXSource>("", false, _audioFacade, false);

	auto testScene = _sceneManager.Load("TestScene");
	if (testScene)
	{
		std::cout << "TestScene Loaded succesfully" << std::endl;
	}

	_debugSystem = _reg.CreateSystem<DebugSystem, A, B>();
	_updateSystem = _reg.CreateSystem<UpdateSystem, Transform, BehaviourScript*>();
	_renderSystem = _reg.CreateSystem<RenderSystem, Transform, Sprite>();

	_window.SetViewportSize(400, 400);
	_window.SetViewportPos(100, 50);
	_window.RenderViewport(255, 255, 255, 255);

	_renderSystem->SetWindow(&_window);
	_renderSystem->SetViewportData(_window.GetViewport());
}

Application::~Application()
{
	Stop();
}

void Application::Run()
{
	_updateSystem->OnStart();
	_renderSystem->OnStart();

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

		_window.Update();		

		// Setting up viewport of window
		


		// Input
		Input(_dt);
		_debugSystem->Update();

		// Update
		//b2World_Step(Singleton::get_instance()._worldId, Temp::TIME_STEP, Temp::SUB_STEP_COUNT);
		_updateSystem->Update();
		//_physicsSystem->Update();
		
		// Render
		_renderSystem->Update();
		//_fontRenderSystem->Update();

		ShowFpsInWindowTitleBar();

		// Framerate
		Rendering::Delay(1000 / 60);
	}
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
