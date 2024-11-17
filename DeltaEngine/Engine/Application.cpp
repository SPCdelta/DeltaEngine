#include "Application.hpp"

bool Application::_isRunning = true;

Application::Application()
	: _window("Delta Engine!", 1280, 720)
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

	GameObject* gameObject = new GameObject( _reg );
	gameObject->AddComponent<A>();
	gameObject->AddComponent<B>();
	gameObject->AddComponent<TempInput>();
	//gameObject->AddComponent<TempBehaviour>();

	_debugSystem = _reg.CreateSystem<DebugSystem, A, B>();
	_updateSystem = _reg.CreateSystem<UpdateSystem, Transform, BehaviourScript*>();
}

Application::~Application()
{
	Stop();
}

void Application::Run()
{
	_updateSystem->OnStart();

	while (!_window.ShouldWindowClose())
	{
		Rendering::PollEvent(_windowEvent);

		if (!Application::_isRunning || _windowEvent.type == Rendering::QUIT)
		{
			Stop();
			break;
		}

		Rendering::GetWindowSize(_window, &_viewportData.width, &_viewportData.height);
		
		_inputFacade.onInputEvent(_windowEvent);
		InputManager::GetInstance().executeInputEvents();


		GetDeltaTime();

		_window.Update();
		Rendering::SetRenderDrawColor(_window.GetRenderer(), 10, 10, 10, 255);
		Rendering::RenderClear(_window.GetRenderer());

		// Input
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
