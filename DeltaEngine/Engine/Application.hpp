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
		TextureManager::Cleanup();
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
	static bool _isRunning;

	Window _window;
	Rendering::Event _windowEvent{};
	InputFacade _inputFacade;

	SceneManager _sceneManager{}; // Never ever pass this variable!

	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;

	// Debug
	Rendering::Color textColor{ 255, 0, 0, 255 };
	Transform _textTransform { { 10.0f, 10.0f }, 0.0f, { 200.0f, 100.0f } };
	Ui::Text* _fpsText = nullptr;
	float _fpsTimer = 1.0f;
	bool _renderFps = true;
	void Debug();
};

