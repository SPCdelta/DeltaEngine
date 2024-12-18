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

#include "GameObject.hpp"
#include "UI/Text.hpp"

#include "Core/Time.hpp"

class SceneHelper;

class Application
{
public:
	Application(int unitPixelSize);
	~Application();

	friend class Scene;
	friend class SceneHelper;

	void Run();

	template<typename T>
	void RegisterScene(const std::string& sceneName)
	{
		_sceneManager.RegisterScene<T>(sceneName);
	}

	void LoadScene(const std::string& sceneName);

	template<typename T>
	void LoadScene(const std::string& sceneName, T* userData)
	{
		SetUserData(reinterpret_cast<void*>(userData));
		_sceneManager.Load(sceneName);
		std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
		currentScene->_inputfacade = &_inputFacade;
		currentScene->_windowEvent = &_windowEvent;
		currentScene->_application = this;
		currentScene->SetWindow(_window);
		currentScene->Start();
	}

	static void Quit()
	{
		_isRunning = false;
	}

	void Stop()
	{
		ResourceManager::Cleanup();
		_window.Close();
		_isRunning = false;

		Rendering::Quit();
		TTF_Quit();
		Rendering::QuitImage();
		Mix_Quit();
	}

	void SetViewport(int sizeWidth, int sizeHeight, int xPos, int yPos)
	{
		_window.SetViewportSize(sizeWidth, sizeHeight);
		_window.SetViewportPos(xPos, yPos);
	}

protected:
	ecs::Registry _reg;

private:
	InputHandler _inputListeners;
	static bool _isRunning;
	void* _userData = nullptr;

	Window _window;
	Rendering::Event _windowEvent{};
	InputFacade _inputFacade;

	SceneManager _sceneManager{}; // Never ever pass this variable!

	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;

	// Debug
	Rendering::Color _debugTextColor{ 255, 0, 0, 255 };
	Transform _debugTextTransform { { 10.0f, 10.0f }, 0.0f, { 200.0f, 100.0f } };
	Ui::Text* _fpsText = nullptr;
	float _fpsTimer = 1.0f;
	bool _renderFps = false;

	void Debug();
	void InitDebug();

	// Gamespeed
	Rendering::Color _gameSpeedTextColor{ 0, 0, 0, 255 };
	std::unique_ptr<Ui::Text> _gameSpeed;
	void InitGameSpeed();
	void RenderGameSpeed();

	// Data
	void* GetUserData() { return _userData; }
	void SetUserData(void* userData) { _userData = userData; }
};

