#pragma once

#include "Window.hpp"

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"
#include "../Rendering/Sprite.hpp"

class RenderSystem : public ecs::System<Transform, Sprite*>
{
public:
	RenderSystem(ecs::View<Transform, Sprite*> view) : ecs::System<Transform, Sprite*>(view)
	{
		
	}

	void SetWindow(Window* window) { _window = window; }

	void SetViewportData(ViewportData* viewportData) { _viewportData = viewportData; }

	void OnStart()
	{ 
		Rendering::GetWindowSize(static_cast<SDL_Window*>(*_window), &_viewportData->width, &_viewportData->height);
		Rendering::SetRenderDrawColor(_window->GetRenderer(), 10, 10, 10, 255);
		Rendering::RenderPresent(_window->GetRenderer());

		for (ecs::EntityId entityId : _view)
		{
			/*Math::Vector2 pos = _view.get<Transform*>(entityId)->position;
			Math::Vector2 sca = _view.get<Transform*>(entityId)->position;
			_view.get<Sprite*>(entityId)->Render(_window->GetRenderer(), pos, sca);*/
		}
	}

	void Update()
	{
		// TODO render each active sprite ?
	}

private:
	Window* _window;
	ViewportData* _viewportData;
};