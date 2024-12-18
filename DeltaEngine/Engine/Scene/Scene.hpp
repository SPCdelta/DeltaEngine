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
class SceneHelper;

class Scene
{
   public:
	Scene(const std::string& name);

	friend class Application;
	friend class SceneHelper;

	const std::string& GetName() const;

	Window* GetWindow() { return _renderSystem->GetWindow(); }
	void SetWindow(Window& window)
	{
		_renderSystem->SetWindow(&window);
		_renderSystem->SetViewportData(&window.GetViewport());
		_imageRenderSystem->SetWindow(&window);
		_imageRenderSystem->SetViewportData(&window.GetViewport());
		_textRenderSystem->SetWindow(&window);
		camera->SetViewportData(&window.GetViewport());
	}

	void LoadScene(const std::string& name);
	void LoadScene(const std::string& name, void* userData);

	virtual void OnStart(){};
	void DestroyObject(GameObject* gameObject)
	{
		auto it = std::find_if(_objects.begin(), _objects.end(),
			[gameObject](const std::shared_ptr<GameObject>& obj)
			{ 
				return obj.get() == gameObject; 
			}
		);

		if (it != _objects.end())
		{
			ecs::EntityId toDestroy = gameObject->_id;
			_objects.erase(it);
			_reg.DestroyEntity(toDestroy);
		}
	}

	void Start();
	void Update();

	void* GetUserData();
	void SetUserData(void* userData);

	std::shared_ptr<GameObject> Instantiate(Transform transform);
	std::shared_ptr<GameObject> Instantiate();

protected:
	Camera* camera;

	void DestroyObject(std::shared_ptr<GameObject> gameObject) { gameObject->Destroy(gameObject.get()); }
	void DestroyPointerObject(GameObject* gameObject) { gameObject->Destroy(gameObject); }

private:
	InputFacade* _inputfacade = nullptr;
	Rendering::Event* _windowEvent = nullptr;
	Application* _application = nullptr;

	ecs::Registry _reg;
	std::string _name;
	std::vector<std::shared_ptr<GameObject>> _objects{};

	std::shared_ptr<GameObject> _cameraObj;

	Physics::PhysicsWorld _physicsWorld{};

	// Systems
	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;
	std::shared_ptr<TextRenderSystem> _textRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;
	std::shared_ptr<ParticleSystem> _particleSystem;
	std::shared_ptr<RenderSystem> _renderSystem;
	std::shared_ptr<ImageRenderSystem> _imageRenderSystem;

	// Destroy
	std::queue<GameObject*> _toDeleteQueue{};
	void MarkForDestroy(GameObject* gameObject)
	{
		_toDeleteQueue.push(gameObject);
	}
};