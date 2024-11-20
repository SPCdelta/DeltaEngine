#pragma once

#include "Window.hpp"

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"
#include "../Rendering/Sprite.hpp"

class RenderSystem : public ecs::System<Transform, Sprite>
{
public:
	RenderSystem(ecs::View<Transform, Sprite> view) : ecs::System<Transform, Sprite>(view), _window(nullptr), _viewportData(nullptr)
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

		Rendering::GetWindowSize(static_cast<Rendering::Window*>(*_window), &_viewportData->width, &_viewportData->height);
	}

	void Update()
	{
		// TODO render background every update (and clear it) to prevent sprite after-image
		//		wait for layer and/or background before finishing this
		/*if (_backgroundTexture)
		{
			Rendering::RenderCopy(_window->GetRenderer(), _backgroundTexture, NULL, NULL);
		}
		else
		{*/
			Rendering::SetRenderDrawColor(_window->GetRenderer(), 10, 10, 10, 255);
			Rendering::RenderClear(_window->GetRenderer());
		/*}*/

		for (ecs::EntityId entityId : _view)
		{
			Transform& transform = _view.get<Transform>(entityId);
			Sprite& sprite = _view.get<Sprite>(entityId);

			const Rendering::UnsignInt8* keys = Rendering::GetKeyboardState(NULL);
			Direction direction = Direction::NONE;

			// Determine direction based on keyboard input
			if (keys[Rendering::SCANCODE_W])
				direction = Direction::UP;
			else if (keys[Rendering::SCANCODE_A])
				direction = Direction::LEFT;
			else if (keys[Rendering::SCANCODE_S])
				direction = Direction::DOWN;
			else if (keys[Rendering::SCANCODE_D])
				direction = Direction::RIGHT;

			// Check if the sprite has an animator, and call Play
			if (sprite.GetAnimator())			
				sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), _viewportData->height, direction);

			// Render the sprite associated with this entity		
			sprite.Render(_window->GetRenderer(), &transform.position, _viewportData->height);
		}

		Rendering::RenderPresent(_window->GetRenderer());
	}

private:
	Window* _window;
	ViewportData* _viewportData;
};