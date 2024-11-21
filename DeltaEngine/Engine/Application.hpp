#pragma once

#include "Rendering/Rendering.hpp"

#include <iostream>
#include <unordered_map>
#include <functional>

#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Window.hpp"

#include "Scene/SceneManager.hpp"
#include "Core/Events/EventDispatcher.hpp"

//Temp
#include "GameObject.hpp"
#include "UI/Text.hpp"


class Application
{
public:
	Application();
	~Application();

	void Run();

	template<typename T>
	void RegisterScene(const std::string& sceneName)
	{
		_sceneManager.RegisterScene<T>(sceneName);
	}

	Events::EventDispatcher<const std::string&> ChangeScene{};

	void LoadScene(const std::string& sceneName)
	{
		_sceneManager.Load(sceneName);
		std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
		currentScene->_changeSceneEvent.Register([this](const std::string& name) { ChangeScene.Dispatch(name); });
		currentScene->SetWindow(_window);
	}

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

	void GetDeltaTime();
	void ShowFpsInWindowTitleBar();
};

