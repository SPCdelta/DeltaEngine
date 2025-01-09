#pragma once

#include "../Ecs/Include.hpp"

#include "../Window.hpp"
#include "../Rendering/Sprite.hpp"

class RenderSystem : public ecs::System<Transform, Sprite>
{
public:
	RenderSystem(ecs::Registry& reg, Camera* camera) 
		: ecs::System<Transform, Sprite>(reg), _window(nullptr), _viewportData(nullptr), _camera{ camera }
	{
		
	}

	Window* GetWindow() { return _window; }
	void SetWindow(Window* window) { _window = window; }

	void SetViewportData(ViewportData* viewportData) { _viewportData = viewportData; }

	void OnStart()
	{ 
		if (!_window || !_viewportData)
		{
			std::cerr << "Error: Window or ViewportData not set in RenderSystem" << std::endl;
			return;
		}
	}

	void Update()
	{
		RefreshView();
		//_window->RenderViewport(255, 255, 255, 255);

		// Collect entities and sort by layer
		std::vector<ecs::EntityId> entities(_view.begin(), _view.end());
		std::sort(entities.begin(), entities.end(), [this](ecs::EntityId a, ecs::EntityId b) 
		{
			int layerA = static_cast<int>(_view.get<Sprite>(a).GetLayer());
			int layerB = static_cast<int>(_view.get<Sprite>(b).GetLayer());
			return layerA < layerB; // Lower layers render first
		});

		for (ecs::EntityId entityId : entities)
		{
			Transform& transform = _view.get<Transform>(entityId);
			Sprite& sprite = _view.get<Sprite>(entityId);

			// Render the sprite associated with this entity
			if (sprite.GetVisible())
				sprite.Render(_window->GetRenderer(), *_viewportData, _camera, transform);
		}
	}

private:
	Window* _window;
	ViewportData* _viewportData;
	Camera* _camera;
};