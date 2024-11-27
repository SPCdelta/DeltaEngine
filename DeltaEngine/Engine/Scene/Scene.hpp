#pragma once

#include <iostream>
#include <string>

#include "../GameObject.hpp"

#include "../Window.hpp"

#include "../Core/Events/EventDispatcher.hpp"
#include "../Audio/AudioFacade.hpp"

// Systems
#include "../Ecs/Registry.hpp"
#include "../Systems/UpdateSystem.hpp"
#include "../Systems/DebugSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/PhysicsSystem.hpp"

class Application;

class Scene
{
   public:
	Scene(const std::string& name);

	friend class Application;

	const std::string& const GetName() const;
	void SetWindow(Window& window)
	{
		_renderSystem->SetWindow(&window);
		_renderSystem->SetViewportData(&window.GetViewport());
		_camera->SetViewportData(&window.GetViewport());
	}

	void LoadScene(const std::string& name)
	{
		_changeSceneEvent.Dispatch(name);
	}

	void Start();
	void Update();

	std::shared_ptr<GameObject> Instantiate(Transform transform);


private:
	Audio::AudioFacade _audioFacade{};
	ecs::Registry _reg;
	std::string _name;
	std::vector<std::shared_ptr<GameObject>> _objects{};
	Events::EventDispatcher<const std::string&> _changeSceneEvent{};
	Events::EventDispatcher<std::shared_ptr<GameObject>> _instantiateEvent{};

	std::shared_ptr<GameObject> _cameraObj;
	Camera* _camera;

	Physics::PhysicsWorld _physicsWorld{};

	// Systems
	std::shared_ptr<DebugSystem> _debugSystem;
	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;
	//std::shared_ptr<FontRenderSystem> _fontRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;
	std::shared_ptr<RenderSystem> _renderSystem;
};