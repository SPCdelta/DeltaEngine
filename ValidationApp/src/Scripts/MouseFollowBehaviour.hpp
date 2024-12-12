#pragma once

#include <Engine/Delta.hpp>

class MouseFollowBehaviour : public BehaviourScript
{
public:
	void OnStart() override 
	{ 
		gameObject->AddComponent<Sprite>("player")->SetLayer(Layer::Foreground);
		_camera = gameObject->GetCamera();

		InputManager::onMouseMove(
			[this](Input& e) 
			{
				mouseX = e.mouseX;
				mouseY = e.mouseY;
			}
		);
	}

	void OnUpdate() override 
	{ 
		Math::Vector2 mouseToWorldPos{ _camera->ScreenToWorldPoint({mouseX, mouseY}) };
		gameObject->transform->position.Set(mouseToWorldPos - 0.5f);
	}

private:
	Camera* _camera = nullptr;
	int mouseX{ 0 };
	int mouseY { 0 };
};