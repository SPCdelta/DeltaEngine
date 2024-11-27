#pragma once

#include "../Ecs/Registry.hpp"

#include "../Window.hpp"
#include "../Rendering/Sprite.hpp"

class RenderSystem : public ecs::System<Transform, Sprite>
{
public:
	RenderSystem(ecs::View<Transform, Sprite> view, Camera* camera) 
		: ecs::System<Transform, Sprite>(view), _window(nullptr), _viewportData(nullptr), _camera{ camera }
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
		// TODO render background every update (and clear it) to prevent sprite after-image
		//		wait for layer and/or background before finishing this
		/*if (_backgroundTexture)
		{
			Rendering::RenderCopy(_window->GetRenderer(), _backgroundTexture, 0, 0);
		}
		else
		{*/
			Rendering::RenderClear(_window->GetRenderer());
			/*_window->RenderViewport(255, 255, 255, 255);*/
		/*}*/

		// Collect entities and sort by layer
		std::vector<ecs::EntityId> entities(_view.begin(), _view.end());
		std::sort(entities.begin(), entities.end(), [this](ecs::EntityId a, ecs::EntityId b) 
		{
			int layerA = static_cast<int>(_view.get<Sprite>(a).GetLayer());
			int layerB = static_cast<int>(_view.get<Sprite>(b).GetLayer());
			return layerA < layerB; // Lower layers render first
		});

		for (ecs::EntityId entityId : _view)
		{
			Transform& transform = _view.get<Transform>(entityId);
			Sprite& sprite = _view.get<Sprite>(entityId);

			/*int windowWidth, windowHeight;
			Rendering::GetWindowSize(static_cast<Rendering::Window*>(*_window), &windowWidth, &windowHeight);

			// Check if the sprite has an animator, and call Play
			if (sprite.GetAnimator())
				sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::NONE);*/

			// Render the sprite associated with this entity
			sprite.Render(_window->GetRenderer(), *_viewportData, _camera, transform);
		}

		Rendering::RenderPresent(_window->GetRenderer());
	}

private:
	Window* _window;
	ViewportData* _viewportData;
	Camera* _camera;
};