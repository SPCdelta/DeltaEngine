#pragma once

#include "Window.hpp"

#include "../Rendering/Sprite.hpp"

class RenderSystem : public ecs::System<Transform, Sprite*>
{
   public:
	RenderSystem(ecs::View<Transform, Sprite*> view) : ecs::System<Transform, Sprite*>(view)
	{
	}

	void OnStart(Window _window, ViewportData _viewportData)
	{ 
		Rendering::GetWindowSize(_window, &_viewportData.width, &_viewportData.height);
		Rendering::SetRenderDrawColor(_window.GetRenderer(), 10, 10, 10, 255);
		Rendering::RenderPresent(_window.GetRenderer());

		for (ecs::EntityId entityId : _view)
		{
			_view.get<Sprite*>(entityId)->Render(_window.GetRenderer(), _view.get<Transform*>(entityId)->position, _view.get<Transform*>(entityId)->scale);
		}
	}

	void Update()
	{
		// TODO render each active sprite ?
	}
};