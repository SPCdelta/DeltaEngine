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

#include "../Core/Files/Json.hpp"

// Systems
#include "../Ecs/Registry.hpp"
#include "../Systems/UpdateSystem.hpp"
#include "../Systems/ParticleSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/PhysicsSystem.hpp"
#include "../Systems/ImageRenderSystem.hpp"
#include "../Systems/TextRenderSystem.hpp"
#include "../Systems/LifetimeSystem.hpp"

struct Velocity
{
	float dx;
	float dy;
};

class Application;
class SceneHelper;

class Scene
{
   public:
	Scene(const std::string& name);
	virtual ~Scene() = default;

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

	virtual void OnStart(){};
	virtual void OnUpdate(){};

	void Start();
	void Update();


	std::shared_ptr<GameObject> Instantiate(Transform transform);
	std::shared_ptr<GameObject> Instantiate();

	// Data
	Json::json& RetriveUserData();
	void StoreUserData(const std::string& data);
	void StoreUserData(Json::json data);
	void DeleteUserData();

protected:
	Camera* camera;

private:
	InputFacade* _inputfacade = nullptr;
	Rendering::Event* _windowEvent = nullptr;
	Application* _application = nullptr;

	ecs::Registry _reg;
	std::string _name;
	//std::vector<std::shared_ptr<GameObject>> _objects{};

	std::shared_ptr<GameObject> _cameraObj;

	Physics::PhysicsWorld _physicsWorld{};

	// Systems
	//std::shared_ptr<UpdateSystem> _updateSystem;
	std::shared_ptr<BehaviourSystem> _behaviourSystem;
	std::shared_ptr<Physics::PhysicsSystem> _physicsSystem;
	std::shared_ptr<TextRenderSystem> _textRenderSystem;
	std::shared_ptr<ParticleSystem> _particleSystem;
	std::shared_ptr<RenderSystem> _renderSystem;
	std::shared_ptr<ImageRenderSystem> _imageRenderSystem;
	std::shared_ptr<LifetimeSystem> _lifetimeSystem;
};