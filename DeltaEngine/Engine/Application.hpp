#pragma once

#include "Rendering/Rendering.hpp"

#include <functional>
#include <iostream>
#include <unordered_map>

#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Window.hpp"

#include "Core/Events/EventDispatcher.hpp"
#include "Scene/SceneManager.hpp"

#include "Physics/BoxCollider.hpp"
#include "Physics/CircleCollider.hpp"
#include "Systems/PhysicsSystem.hpp"

//Temp
#include "GameObject.hpp"
#include "UI/Text.hpp"

class Application
{
public:
	Application(int unitPixelSize);
	~Application();

	void Run();

	Events::EventDispatcher<const std::string&> ChangeScene{};

	template<typename T>
	void RegisterScene(const std::string& sceneName)
	{
		_sceneManager.RegisterScene<T>(sceneName);
	}

	void LoadScene(const std::string& sceneName);

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

	SceneManager _sceneManager{}; // Never ever pass this variable!

	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;

	void GetDeltaTime();
	void ShowFpsInWindowTitleBar();
};

