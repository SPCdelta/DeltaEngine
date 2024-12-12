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

void Scene::DestroyObject(GameObject* gameObject)
{
	size_t toDelete = 0;
	bool found = false;

	for (size_t i = 0 ; i < _objects.size(); i++)
	{
		if (_objects[i].get() == gameObject)
		{
			toDelete = i;
			found = true;
			break;
		}
	}

	if (found)
	{
		gameObject->deleted = true;
		_reg.DestroyEntity(gameObject->_id);
		_objects.erase(_objects.begin() + toDelete);
	}
	else
	{
		int bp = 0;
		std::cout << "Scene: OBJECT TO BE DELETED NOT FOUND!" << std::endl;
	}
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

	// Render
	_renderSystem->Update();
	_imageRenderSystem->Update();
	_textRenderSystem->Update();
}

GameObject* Scene::Instantiate(Transform transform)
{
	std::unique_ptr<GameObject>& obj = _objects.emplace_back(std::make_unique<GameObject>(_reg, _physicsWorld, _changeSceneEvent, _camera, transform));
	obj->transform->gameObject = obj.get();

	// Allow Instantiation
	obj->_instantiatePromise.Register(
		[this](GameObject*& e)
		{ 
			e = Instantiate({{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}});
		}
	);
	obj->_destroyObject.Register([this](GameObject* gameObject)
		{ 
			DestroyObject(gameObject);
			//MarkForDestroy(gameObject);
		}
	);

	return obj.get();
}
