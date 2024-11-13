#include "Application.hpp"

bool Application::_isRunning = true;

Application::Application()
	: _window("Meow!", 1280, 720)
{
	// Init SDL2
	if (Rendering::Facade::Initialize(Rendering::INIT_VIDEO |
									  Rendering::INIT_AUDIO) < 0)
	{
		std::cerr << "Failed to initialize the SDL2 library" << std::endl;
	}

	// Init SDL2_image
	if (!(Rendering::Facade::InitializeImage(Rendering::INIT_PNG) &
		  Rendering::INIT_PNG))
	{
		std::cerr << "Failed to initialize the SDL2_image library" << std::endl;
	}

	// Init SDL2_ttf
	if (TTF_Init() < 0)
	{
		std::cerr << "Failed to initialize the SDL2_ttf library" << std::endl;
	}

	//
	ecs::EntityId debug = _reg.CreateEntity();
	_reg.AddComponent<A>(debug, {});
	_reg.AddComponent<B>(debug, {});

	_debugSystem = _reg.CreateSystem<DebugSystem, A, B>();
}

Application::~Application()
{
	Stop();
}

void Application::Run()
{
	//_updateSystem->OnStart();

	while (!_window.ShouldWindowClose())
	{
		Rendering::Facade::PollEvent(_windowEvent);

		if (!Application::_isRunning || _windowEvent.type == Rendering::QUIT)
		{
			Stop();
			break;
		}

		Rendering::Facade::GetWindowSize(_window, &_viewportData.width,
										 &_viewportData.height);

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

		Rendering::Facade::SetRenderDrawColor(_window.GetRenderer(), 10, 10, 10,
											  255);
		Rendering::Facade::RenderClear(_window.GetRenderer());

		// Input
		Input(_dt);
		_debugSystem->Update();

		// Update
		//b2World_Step(Singleton::get_instance()._worldId, Temp::TIME_STEP, Temp::SUB_STEP_COUNT);
		//_updateSystem->Update();
		//_physicsSystem->Update();

		// Render
		//_renderSystem->Update();
		//_fontRenderSystem->Update();
		Rendering::Facade::RenderPresent(_window.GetRenderer());

		ShowFpsInWindowTitleBar();

		// Framerate
		Rendering::Facade::Delay(1000 / 60);
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
