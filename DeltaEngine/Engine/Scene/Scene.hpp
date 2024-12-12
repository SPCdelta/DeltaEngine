#pragma once

#include <iostream>
#include <string>
#include <queue>

#include "../GameObject.hpp"

#include "../Window.hpp"

#include "../Core/Events/EventDispatcher.hpp"
#include "../Audio/AudioManager.hpp"
#include "../Rendering/Renderables/Renderable.hpp"

#include "../Input/InputManager.hpp"
#include "../Input/InputFacade.hpp"

// Systems
#include "../Ecs/Registry.hpp"
#include "../Systems/UpdateSystem.hpp"
#include "../Systems/ParticleSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/PhysicsSystem.hpp"
#include "../Systems/ImageRenderSystem.hpp"
#include "../Systems/TextRenderSystem.hpp"

class Application;

class Scene
{
   public:
	Scene(const std::string& name);

	friend class Application;

	const std::string& GetName() const { return _name; }

	Window* GetWindow() { return _renderSystem->GetWindow(); }
	void SetWindow(Window& window)
	{
		_renderSystem->SetWindow(&window);
		_renderSystem->SetViewportData(&window.GetViewport());
		_imageRenderSystem->SetWindow(&window);
		_imageRenderSystem->SetViewportData(&window.GetViewport());
		_textRenderSystem->SetWindow(&window);
		_camera->SetViewportData(&window.GetViewport());
	}

	void LoadScene(const std::string& name)
	{
		_changeSceneEvent.Dispatch(name);
	}

	virtual void OnStart(){};
	void DestroyObject(GameObject* gameObject);

	void Start();
	void Update();

	GameObject* Instantiate(Transform transform);

private:
	InputFacade* _inputfacade = nullptr;
	Rendering::Event* _windowEvent = nullptr;

	ecs::Registry _reg;
	std::string _name;
	std::vector<std::unique_ptr<GameObject>> _objects{};
	Events::EventDispatcher<const std::string&> _changeSceneEvent{};
	Events::EventDispatcher<GameObject*> _instantiateEvent{};

	GameObject* _cameraObj;
	Camera* _camera;

	Physics::PhysicsWorld _physicsWorld{};

	// Systems
	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;
	std::shared_ptr<TextRenderSystem> _textRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;
	std::shared_ptr<ParticleSystem> _particleSystem;
	std::shared_ptr<RenderSystem> _renderSystem;
	std::shared_ptr<ImageRenderSystem> _imageRenderSystem;

	// Destroy
	//std::queue<GameObject*> _toDeleteQueue{};
	//void MarkForDestroy(GameObject* gameObject)
	//{
	//	_toDeleteQueue.push(gameObject);
	//}
};