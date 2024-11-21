#pragma once

#include <iostream>
#include <string>

#include "../Ecs/Registry.hpp"
#include "../GameObject.hpp"
#include "../Window.hpp"

// Systems
#include "../Systems/UpdateSystem.hpp"
#include "../Systems/DebugSystem.hpp"
#include "../Systems/RenderSystem.hpp"

// Temp | TODO: remove when done
//#include "../Temp/TempBehaviour.hpp"

class Scene
{
public:
	Scene(const std::string& name);

	const std::string& const GetName() const;
	void SetWindow(Window& window)
	{
		_renderSystem->SetWindow(&window);
		_renderSystem->SetViewportData(window.GetViewport());
	}

	void Start();
	void Update();

	std::shared_ptr<GameObject> Instantiate(Transform transform);

private:
	ecs::Registry _reg;
	std::string _name;
	std::vector<std::shared_ptr<GameObject>> _objects{};

	// Systems
	std::shared_ptr<DebugSystem> _debugSystem;
	//std::shared_ptr<PhysicsSystem> _physicsSystem;
	//std::shared_ptr<FontRenderSystem> _fontRenderSystem;
	std::shared_ptr<UpdateSystem> _updateSystem;
	std::shared_ptr<RenderSystem> _renderSystem;
};