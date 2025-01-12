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
#include "Scene/UserDataStorage.hpp"

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

	friend class Scene;

	void Run();

	template<typename T>
	void RegisterScene(const std::string& sceneName)
	{
		_sceneManager.RegisterScene<T>(sceneName);
	}

	void LoadScene(const std::string& sceneName);

	static void Quit();
	void Stop();

	void SetViewport(int sizeWidth, int sizeHeight, int xPos, int yPos);

	// Data
	Json::json& RetriveData();
	void StoreData(const std::string& data);
	void StoreData(Json::json& data);
	void DeleteUserData();

protected:
	ecs::Registry _reg;

private:
	const int BASE_WINDOW_W = 1280;
	const int BASE_WINDOW_H = 720;

	InputHandler _inputListeners;
	
	static bool _isRunning;
	StoreUserData _userData;

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
	bool _renderDebug = false;

	void Debug();
	void InitDebug();
	void InitGameSpeed();

	// Gamespeed
	Rendering::Color _gameSpeedTextColor{ 255, 0, 0, 255 };
	std::unique_ptr<Ui::Text> _gameSpeed;
};
