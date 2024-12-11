#pragma once

#include <iostream>
#include <string>

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

	const std::string& const GetName() const;

	Window* GetWindow() { return _renderSystem->GetWindow(); }
	void SetWindow(Window& window)
	{
		_renderSystem->SetWindow(&window);
		_renderSystem->SetViewportData(&window.GetViewport());
		_imageRenderSystem->SetWindow(&window);
		_imageRenderSystem->SetViewportData(&window.GetViewport());
		_textRenderSystem->SetWindow(&window);
		_camera->SetViewportData(&window.GetViewport());
		std::cout << (_camera != nullptr ? std::to_string(_camera->GetunitPixelSize()) : "Null");
	}

	void LoadScene(const std::string& name)
	{
		_changeSceneEvent.Dispatch(name);
	}

	virtual void OnStart(){};
	void DestroyObject(GameObject* gameObject)
	{
		auto it = std::remove_if(_objects.begin(), _objects.end(),
			[gameObject](const std::shared_ptr<GameObject>& obj)
			{ 
				return obj.get() == gameObject; 
			}
		);

		if (it != _objects.end())
		{
			_reg.DestroyEntity(gameObject->_id);
			_objects.erase(it, _objects.end());
		}
	}

	void Start();
	void Update();

	std::shared_ptr<GameObject> Instantiate(Transform transform);

protected:
	Camera* _camera;


private:
	InputFacade* _inputfacade = nullptr;
	Rendering::Event* _windowEvent = nullptr;

	ecs::Registry _reg;
	std::string _name;
	std::vector<std::shared_ptr<GameObject>> _objects{};
	Events::EventDispatcher<const std::string&> _changeSceneEvent{};
	Events::EventDispatcher<std::shared_ptr<GameObject>> _instantiateEvent{};

	std::shared_ptr<GameObject> _cameraObj;

	Physics::PhysicsWorld _physicsWorld{};

	// Systems
	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;
	std::shared_ptr<TextRenderSystem> _textRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;
	std::shared_ptr<RenderSystem> _renderSystem;
	std::shared_ptr<ImageRenderSystem> _imageRenderSystem;
};