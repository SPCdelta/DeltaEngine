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
		// moved to Application cpp run loop
		/*}*/

		for (ecs::EntityId entityId : _view)
		{
			Transform& transform = _view.get<Transform>(entityId);
			Sprite& sprite = _view.get<Sprite>(entityId);

			// TODO this movement/keys code is for testing, this needs to be integrated with input once input is done and on main)
			const Rendering::UnsignInt8* keys = Rendering::GetKeyboardState(0);
			Direction direction = Direction::NONE;

			// TODO bind to sdl event when mouse is clicked, for testing you can add it in with the else if underneath,
			//		however, when doing this holding space will have the sprite be mid attack animation
			/*if (keys[Rendering::SCANCODE_SPACE])
			{
				sprite.GetSheet()->Attack();
			}*/

			// Determine direction based on keyboard input
			if (keys[Rendering::SCANCODE_W])
				direction = Direction::UP;
			else if (keys[Rendering::SCANCODE_A])
				direction = Direction::LEFT;
			else if (keys[Rendering::SCANCODE_S])
				direction = Direction::DOWN;
			else if (keys[Rendering::SCANCODE_D])
				direction = Direction::RIGHT;

			int windowWidth, windowHeight;
			Rendering::GetWindowSize(static_cast<Rendering::Window*>(*_window), &windowWidth, &windowHeight);

			// Check if the sprite has an animator, and call Play
			if (sprite.GetAnimator())
				sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, direction);
			// TODO (see prev TODO text, this is just the end of the mentioned code) ^^

			// Render the sprite associated with this entity
			sprite.Render(_window->GetRenderer(), *_viewportData, _camera, transform);
		}
	}

private:
	Window* _window;
	ViewportData* _viewportData;
	Camera* _camera;
};