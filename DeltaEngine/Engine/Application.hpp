#pragma once

#include "Rendering/Rendering.hpp"

#include <iostream>

#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Window.hpp"

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

		Rendering::Quit();
		TTF_Quit();
		Rendering::QuitImage();
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
	Rendering::Event _windowEvent{};

	// Engine?
	std::shared_ptr<DebugSystem> _debugSystem;
	//std::shared_ptr<PhysicsSystem> _physicsSystem;
	//std::shared_ptr<FontRenderSystem> _fontRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;

	void GetDeltaTime();
	void ShowFpsInWindowTitleBar();
};

