#pragma once

#include "Window.hpp"

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"
#include "../Rendering/Sprite.hpp"

class RenderSystem : public ecs::System<Transform*, Sprite*>
{
public:
	RenderSystem(ecs::View<Transform*, Sprite*> view) : ecs::System<Transform*, Sprite*>(view), _window(nullptr), _viewportData(nullptr)
	{
		
	}

	void SetWindow(Window* window) { _window = window; }

	void SetViewportData(ViewportData* viewportData) { _viewportData = viewportData; }

	void OnStart()
	{ 
		if (!_window || !_viewportData)
		{
			std::cerr << "Error: Window or ViewportData not set in RenderSystem" << std::endl;
			return;
		}

		Rendering::GetWindowSize(static_cast<SDL_Window*>(*_window), &_viewportData->width, &_viewportData->height);
		Rendering::SetRenderDrawColor(_window->GetRenderer(), 10, 10, 10, 255);
		Rendering::RenderPresent(_window->GetRenderer());

		for (ecs::EntityId entityId : _view)
		{
			Transform* transform = _view.get<Transform*>(entityId);
			if (!transform)
			{
				std::cerr << "Error: Missing Transform component on entity" << std::endl;
				continue;
			}

			Math::Vector2 pos = transform->position;
			Math::Vector2 sca = transform->scale;

			// Render the sprite associated with this entity
			Sprite* sprite = _view.get<Sprite*>(entityId);
			if (sprite)
			{
				sprite->Render(_window->GetRenderer(), pos, sca);
			}
			else
			{
				std::cerr << "Error: Missing Sprite component on entity" << std::endl;
			}
		}
	}

	void Update()
	{
		
	}

private:
	Window* _window;
	ViewportData* _viewportData;
};