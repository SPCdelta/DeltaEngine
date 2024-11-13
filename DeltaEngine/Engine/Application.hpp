#pragma once
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <SDL_image.h>
#include "Window.hpp"

#include "Rendering/Viewport.hpp"

#include "Systems/UpdateSystem.hpp"
#include "Systems/DebugSystem.hpp"

//Temp
#include "Temp/TempBehaviour.hpp"
#include "GameObject.hpp"

class Application
{
public:
	Application();
	~Application();

	void Run();

	static void Quit()
	{
		_isRunning = false;
	}

	void Stop()
	{
		_window.Close();
		_isRunning = false;

		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		Mix_Quit();
	}

	virtual void Input(float dt) { }

	//GameObject Instantiate()
	//{
	//	return { _reg };
	//}

protected:
	ecs::Registry _reg;
	//ecs::EntityId camera;
	//Camera* _cameraComponent = nullptr;

private:
	static bool _isRunning;

	float _dt{ 0.0f };

	float _currentFrame{ 0.0f };
	float _lastFrame{ 0.0f };

	float _lastTime{ 0.0f };
	float _nbFrames{ 0.0f };

	Window _window;
	SDL_Event _windowEvent{};
	ViewportData _viewportData{ 50.0f, 1280, 720 };

	// Engine?
	std::shared_ptr<DebugSystem> _debugSystem;
	//std::shared_ptr<PhysicsSystem> _physicsSystem;
	//std::shared_ptr<FontRenderSystem> _fontRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;

	void GetDeltaTime();
	void ShowFpsInWindowTitleBar();
};

