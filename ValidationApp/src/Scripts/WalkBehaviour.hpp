#pragma once

#include "Engine/Delta.hpp"

class WalkBehaviour : public BehaviourScript
{
	public:
		void OnStart() override
		{
			Transform& transform = gameObject->GetComponent<Transform>();
			Sprite& sprite = gameObject->GetComponent<Sprite>();

			int windowWidth, windowHeight; // TODO winhowheight 0/NULL
			if (_window)
				Rendering::GetWindowSize(static_cast<Rendering::Window*>(*_window), &windowWidth, &windowHeight);

			// Check if the sprite has an animator, and call Play

			keyPressed(KEY_W, [&transform, sprite, windowHeight](Input& key) 
			{ 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::UP); 
			},"animation");
			onKeyReleased(KEY_W, [&transform, sprite, windowHeight](Input& key) 
			{
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::NONE); 
			},"animation");

			keyPressed(KEY_A, [&transform, sprite, windowHeight](Input& key) 
			{ 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::LEFT); 
			},"animation");
			onKeyReleased(KEY_A, [&transform, sprite, windowHeight](Input& key) 
			{
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::NONE); 
			},"animation");

			keyPressed(KEY_S, [&transform, sprite, windowHeight](Input& key) 
			{ 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::DOWN); 
			},"animation");
			onKeyReleased(KEY_S, [&transform, sprite, windowHeight](Input& key) 
			{
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::NONE); 
			},"animation");

			keyPressed(KEY_D, [&transform, sprite, windowHeight](Input& key) 
			{ 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::RIGHT); 
			},"animation");
			onKeyReleased(KEY_D, [&transform, sprite, windowHeight](Input& key) 
			{
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(&transform.position, sprite.GetSheet(), windowHeight, Direction::NONE); 
			},"animation");
		}

		void OnUpdate() override
		{

		}

		void SetWindow(Window* window) { _window = window; }

	private:
		Window* _window{nullptr};
};