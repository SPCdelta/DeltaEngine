#include "Scene.hpp"

Scene::Scene(const std::string& name)
	: _name{name}
{
	_cameraObj = Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}});
	_camera = _cameraObj->AddComponent<Camera>(_cameraObj->GetComponent<Transform>());

	_updateSystem =_reg.CreateSystem<UpdateSystem, Transform, BehaviourScript*>();
	_particleSystem = _reg.CreateSystem<ParticleSystem, Transform, ParticleEmitter>();
	_renderSystem = _reg.CreateSystem<RenderSystem, Transform, Sprite>(_camera);
	_imageRenderSystem = _reg.CreateSystem<ImageRenderSystem, Transform, Ui::Image>();
	_textRenderSystem = _reg.CreateSystem<TextRenderSystem, Transform, Ui::Text>();
	_physicsSystem = _reg.CreateSystem<Physics::PhysicsSystem, Transform, Physics::Rigidbody>(_reg, _physicsWorld);
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
	while (!_toDeleteQueue.empty())
	{
		DestroyObject(_toDeleteQueue.front());
		_toDeleteQueue.pop();  // Remove the pointer from the queue
	}

	// Render
	_renderSystem->Update();
	_imageRenderSystem->Update();
	_textRenderSystem->Update();
}

std::shared_ptr<GameObject> Scene::Instantiate(Transform transform)
{
	std::shared_ptr<GameObject> obj{ 
		std::make_shared<GameObject>
		(
			_reg, _physicsWorld, _changeSceneEvent, _camera, transform
		) 
	};
	obj->transform->gameObject = obj.get();
	_objects.push_back(obj);

	// Allow Instantiation
	obj->_instantiatePromise.Register(
		[this](std::shared_ptr<GameObject>& e)
		{ 
			e = Instantiate({{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}});
		}
	);
	obj->_destroyObject.Register([this](GameObject* gameObject)
		{ 
			MarkForDestroy(gameObject); 
		}
	);

	return obj;
}
