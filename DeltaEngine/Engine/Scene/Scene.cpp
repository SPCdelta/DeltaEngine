#include "Scene.hpp"

Scene::Scene(const std::string& name)
	: _name{ name }
{
	_debugSystem = _reg.CreateSystem<DebugSystem, A, B>();
	_updateSystem =_reg.CreateSystem<UpdateSystem, Transform, BehaviourScript*>();
	_renderSystem = _reg.CreateSystem<RenderSystem, Transform, Sprite>();
}

void Scene::Start()
{
	Transform transform{{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}};
	Rendering::Color color{255, 0, 0, 255};

	std::shared_ptr<GameObject> text = Instantiate(transform);
	debugFps = text->AddComponent<ui::Text>("Hello World!", "Assets\\Fonts\\consolas.ttf", 36, 10, 10, color, _window->GetRenderer());

	_updateSystem->OnStart();
	_renderSystem->OnStart();
}

void Scene::Update()
{
	_debugSystem->Update();

	// Update
	//b2World_Step(Singleton::get_instance()._worldId, Temp::TIME_STEP, Temp::SUB_STEP_COUNT);
	_updateSystem->Update();
	//_physicsSystem->Update();

	// Render
	_renderSystem->Update();
	/*debugFps->renderText();*/
	RenderFPS();
	//_fontRenderSystem->Update();
}

std::shared_ptr<GameObject> Scene::Instantiate(Transform transform)
{
	std::shared_ptr<GameObject> obj{ std::make_shared<GameObject>(_reg, _changeSceneEvent, transform) };
	_objects.push_back(obj);
	return obj;
}

void Scene::GetDeltaTime() {
	_currentFrame = Rendering::GetTicks() / 1000.f;
	float deltaTime = _currentFrame - _lastFrame;
	_lastFrame = _currentFrame;
}

void Scene::RenderFPS() {
	_nbFrames++;

	float currentTime = Rendering::GetTicks() / 1000.0f;
	if (currentTime - _lastTime >= 1.0f)
	{
		float fps = _nbFrames / (currentTime - _lastTime);

		_lastTime = currentTime;
		_nbFrames = 0;

		debugFps->SetText("FPS: " + std::to_string(static_cast<int>(fps)));
		debugFps->renderText();
	}

}

const std::string& const Scene::GetName() const 
{
	return _name;
}


