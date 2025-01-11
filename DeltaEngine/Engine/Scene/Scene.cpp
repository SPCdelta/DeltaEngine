#include "Scene.hpp"

#include "../Application.hpp"

Scene::Scene(const std::string& name)
	: _name{name}
{
	_cameraObj = Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}});
	camera = _cameraObj->AddComponent<Camera>(_cameraObj->GetComponent<Transform>());

	//_updateSystem =_reg.CreateSystem<UpdateSystem, Transform, BehaviourScript*>();
	_behaviourSystem = _reg.CreateSystem<BehaviourSystem, std::unique_ptr<BehaviourScript>>();
	_particleSystem = _reg.CreateSystem<ParticleSystem, Transform, ParticleEmitter>();
	_renderSystem = _reg.CreateSystem<RenderSystem, Transform, Sprite>(camera);
	_imageRenderSystem = _reg.CreateSystem<ImageRenderSystem, Transform, Ui::Image>();
	_textRenderSystem = _reg.CreateSystem<TextRenderSystem, Transform, Ui::Text>();
	_physicsSystem = _reg.CreateSystem<Physics::PhysicsSystem, Transform, Physics::Rigidbody>(_physicsWorld);
	_lifetimeSystem = _reg.CreateSystem<LifetimeSystem, Transform, Lifetime>();
	_aStarSystem = _reg.CreateSystem<AStarSystem, Transform, AStarWalkable>();
}

void Scene::LoadScene(const std::string& name)
{
	_application->LoadScene(name);
}

void Scene::Start()
{ 
	_renderSystem->OnStart();
	_textRenderSystem->OnStart();
	OnStart();
}

// The order in this update loop is VERY VERY important
// Do NOT edit this without being 1000% sure the change is good
void Scene::Update()
{
	// Physics
	_physicsSystem->PhysicsEvents();

	// Input
	_inputfacade->onInputEvent(*_windowEvent);
	InputManager::GetInstance().executeInputEvents();

	// Update
	OnUpdate();
	//_updateSystem->Update();
	_behaviourSystem->Update();

	_particleSystem->Update();

	// LateUpdate Physics
	_physicsSystem->TransformToBox2D();
	_physicsSystem->ApplyPhysics();
	_physicsSystem->Box2DToTransform();

	_reg._registry.view<Transform, Velocity>().each([&](auto entity, Transform& transform, Velocity& velocity) 
	{
		transform.position += velocity.velocity * Time::GetDeltaTime();
	});

	_lifetimeSystem->Update();

	// Render
	_renderSystem->Update();
	_imageRenderSystem->Update();
	_textRenderSystem->Update();
}

std::shared_ptr<GameObject> Scene::Instantiate(Transform transform)
{
	// Create Entity Beforehand
	ecs::EntityId entityId = _reg.CreateEntity();
	Transform& transformComponent = _reg.AddComponent<Transform>(entityId, transform);

	// Use entityId for obj
	std::shared_ptr<GameObject> obj
	{ 
		std::make_shared<GameObject>
		(
			this, 
			entityId, 
			_reg, 
			_physicsWorld, 
			camera, 
			transformComponent
		) 
	};
	
	transformComponent.gameObject = obj;
	return obj;
}

std::shared_ptr<GameObject> Scene::Instantiate()
{
	return Instantiate({{1.0f, 1.0f}, 0.0f, {1.0f, 1.0f}});
}

const std::string& Scene::GetName() const
{
	return _name;
}

Json::json& Scene::RetrieveUserData() 
{ 
	return _application->RetriveData(); 
}

void Scene::StoreUserData(const std::string& data) 
{ 
	_application->StoreData(data); 
}

void Scene::StoreUserData(Json::json data)
{
	_application->StoreData(data);
}

void Scene::DeleteUserData() 
{ 
	_application->DeleteUserData(); 
}

Window* Scene::GetWindow()
{
	return _renderSystem->GetWindow();
}

void Scene::SetWindow(Window& window)
{
	_renderSystem->SetWindow(&window);
	_renderSystem->SetViewportData(&window.GetViewport());
	_imageRenderSystem->SetWindow(&window);
	_imageRenderSystem->SetViewportData(&window.GetViewport());
	_textRenderSystem->SetWindow(&window);
	camera->SetViewportData(&window.GetViewport());
}

void Scene::GetWalkableTiles(std::vector<Transform*>& tiles, std::vector<Transform*>& walls)
{
	_aStarSystem->GetWalkableTiles(tiles, walls);
}
