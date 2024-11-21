#pragma once

#include <iostream>
#include <string>

#include "../GameObject.hpp"

#include "../Ecs/Registry.hpp"
#include "../Window.hpp"

#include "../Core/Events/EventDispatcher.hpp"

// Systems
#include "../Systems/UpdateSystem.hpp"
#include "../Systems/DebugSystem.hpp"
#include "../Systems/RenderSystem.hpp"

// Debug
#include "../UI/Text.hpp"

// Temp | TODO: remove when done
//#include "../Temp/TempBehaviour.hpp"

class Application;

class Scene
{
public:
	Scene(const std::string& name);

	friend class Application;

	const std::string& const GetName() const;
	void SetWindow(Window& window)
	{
		_window = &window;
		_renderSystem->SetWindow(&window);
		_renderSystem->SetViewportData(window.GetViewport());
	}

	void LoadScene(const std::string& name) { _changeSceneEvent.Dispatch(name); }

	void Start();
	void Update();

	std::shared_ptr<GameObject> Instantiate(Transform transform);

private:
	ecs::Registry _reg;
	std::string _name;
	std::vector<std::shared_ptr<GameObject>> _objects{};
	Events::EventDispatcher<const std::string&> _changeSceneEvent{};

	// Systems
	std::shared_ptr<DebugSystem> _debugSystem;
	//std::shared_ptr<PhysicsSystem> _physicsSystem;
	//std::shared_ptr<FontRenderSystem> _fontRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;
	std::shared_ptr<RenderSystem> _renderSystem;

	//
	Window* _window = nullptr;
	ui::Text* debugFps = nullptr;
};