#pragma once
#include "../BehaviourScript.hpp"


class Draggable : public BehaviourScript
{
public:
	void OnStart() override
	{
		//gameObject->AddComponent<Sprite>("player")->SetLayer(Layer::Foreground);
		camera = gameObject->GetCamera();

		InputManager::onMouseMove(
			[this](Input& e)
			{
				if (!isDraggable)
					return;

				Math::Vector2 mouseToWorldPos{ camera->ScreenToWorldPoint(e.mouseX, e.mouseY) };
				gameObject->transform->position.Set(mouseToWorldPos - 0.5f);
			}
		);

		InputManager::onMouseButtonDown(MouseButton::Left,
			[this](Input& e)
			{
				if (isDraggable)
					return;
				auto mousevector = camera->ScreenToWorldPoint(e.mouseX, e.mouseY);
				if (Math::MathUtils::IsVector2WithinRect(mousevector, gameObject->transform->position, gameObject->transform->scale)){
					isDraggable = true;
				}

			}
		);

		InputManager::onMouseButtonUp(MouseButton::Left,
			[this](Input& e)
			{
				if (isDraggable)
					isDraggable = false;

			}
		);


	}

private:
	bool isDraggable = true;
};