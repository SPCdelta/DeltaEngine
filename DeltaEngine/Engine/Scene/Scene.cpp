#include "Scene.hpp"

Scene::Scene(const std::string& name)
	: _name{name}
{
	_cameraObj = Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}});
	camera = _cameraObj->AddComponent<Camera>(_cameraObj->GetComponent<Transform>());

	_updateSystem =_reg.CreateSystem<UpdateSystem, Transform, BehaviourScript*>();
	_particleSystem = _reg.CreateSystem<ParticleSystem, Transform, ParticleEmitter>();
	_renderSystem = _reg.CreateSystem<RenderSystem, Transform, Sprite>(camera);
	_imageRenderSystem = _reg.CreateSystem<ImageRenderSystem, Transform, Ui::Image>();
	_textRenderSystem = _reg.CreateSystem<TextRenderSystem, Transform, Ui::Text>();
	_physicsSystem = _reg.CreateSystem<Physics::PhysicsSystem, Transform, Physics::Rigidbody>(_reg, _physicsWorld);
	_despawnSystem = _reg.CreateSystem<DespawnSystem, Transform, Despawner>();
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
	_physicsSystem->ApplyPhysics();
	_physicsSystem->Box2DToTransform();
	_physicsSystem->PhysicsEvents();

	// Input
	_inputfacade->onInputEvent(*_windowEvent);
	InputManager::GetInstance().executeInputEvents();

	// Update
	_updateSystem->Update();
	_particleSystem->Update();

	// LateUpdate
	_physicsSystem->TransformToBox2D();

	// Destroy
	_despawnSystem->Update();
	while (!_toDeleteQueue.empty())
	{
		GameObject* gameObject = _toDeleteQueue.front();
		auto it = std::find_if(_objects.begin(), _objects.end(),
		[gameObject](const std::shared_ptr<GameObject>& obj)
		{ 
			return obj.get() == gameObject; 
		});

		if (it != _objects.end())
		{
			ecs::EntityId toDestroy = gameObject->_id;
			_objects.erase(it);
			_reg.DestroyEntity(toDestroy);
		}

		_toDeleteQueue.pop();  // Remove the pointer from the queue
	}

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
			this, entityId, _reg, _physicsWorld, _changeSceneEvent, camera, transformComponent
		) 
	};
	transformComponent.gameObject = obj.get();
	_objects.push_back(obj);

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
