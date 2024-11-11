#include "Application.hpp"

bool Application::_isRunning = true;

Application::Application()
	: _window("Meow!", 1280, 720)
{
	
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
		SDL_PollEvent(&_windowEvent);

		if (!Application::_isRunning || _windowEvent.type == SDL_QUIT)
		{
			Stop();
			break;
		}

		SDL_GetWindowSize(_window, &_viewportData.width, &_viewportData.height);

		// Internal Input
		if (_windowEvent.type == SDL_KEYDOWN)
		{
			//InputManager::GetInstance().SetKeyState(_windowEvent.key.keysym.scancode, 1.0f);
		}
		else if (_windowEvent.type == SDL_KEYUP)
		{
			//InputManager::GetInstance().SetKeyState(_windowEvent.key.keysym.scancode, 0.0f);
		}

		GetDeltaTime();

		_window.Update();

		SDL_SetRenderDrawColor(_window.GetRenderer(), 10, 10, 10, 255);
		SDL_RenderClear(_window.GetRenderer());

		// Input
		Input(_dt);

		// Update
		//b2World_Step(Singleton::get_instance()._worldId, Temp::TIME_STEP, Temp::SUB_STEP_COUNT);
		//_updateSystem->Update();
		//_physicsSystem->Update();

		// Render
		//_renderSystem->Update();
		//_fontRenderSystem->Update();
		SDL_RenderPresent(_window.GetRenderer());

		ShowFpsInWindowTitleBar();

		// Framerate
		SDL_Delay(1000 / 60);
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