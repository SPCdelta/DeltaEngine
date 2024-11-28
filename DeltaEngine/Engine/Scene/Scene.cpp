#include "Scene.hpp"

Scene::Scene(const std::string& name)
	: _name{name}
{
	_cameraObj = Instantiate({{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}});
	_camera = _cameraObj->AddComponent<Camera>(_cameraObj->GetComponent<Transform>());

	_debugSystem = _reg.CreateSystem<DebugSystem, A, B>();
	_updateSystem =_reg.CreateSystem<UpdateSystem, Transform, BehaviourScript*>();
	_renderSystem = _reg.CreateSystem<RenderSystem, Transform, Sprite>(_camera);
	_imageRenderSystem = _reg.CreateSystem<ImageRenderSystem, Transform, Ui::Image>();
	_textRenderSystem = _reg.CreateSystem<TextRenderSystem, Transform, Ui::Text>();
	_physicsSystem = _reg.CreateSystem<Physics::PhysicsSystem, Transform, Physics::Rigidbody>(_reg, _physicsWorld);

	
}

void Scene::Start()
{ 
	_updateSystem->OnStart();
	_renderSystem->OnStart();
	_textRenderSystem->OnStart();
}

void Scene::Update()
{
	_debugSystem->Update();

	// Update
	_physicsSystem->BeforeBehaviourUpdate();
	_updateSystem->Update();
	_physicsSystem->AfterBehaviourUpdate();

	// Render
	_renderSystem->Update();
	_imageRenderSystem->Update();
	_textRenderSystem->Update();
}

std::shared_ptr<GameObject> Scene::Instantiate(Transform transform)
{
	std::shared_ptr<GameObject> obj{ std::make_shared<GameObject>(_reg, _audioFacade, _physicsWorld, _changeSceneEvent, _camera, transform) };
	obj->transform->gameObject = obj;
	_objects.push_back(obj);

	// Allow Instantiation
	obj->_instantiatePromise.Register(
		[this](std::shared_ptr<GameObject>& e)
		{ 
			e = Instantiate({{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}});
		}
	);

	return obj;
}

const std::string& const Scene::GetName() const 
{
	return _name;
}
