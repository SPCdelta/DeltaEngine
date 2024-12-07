#pragma once
#include "../BehaviourScript.hpp"
#include "../Core/Math/MathUtils.hpp"


class SnapToGridDraggable : public BehaviourScript
{
public:
	void OnStart() override
	{
		camera = gameObject->GetCamera();

		int pxUnit = camera->GetunitPixelSize();

		InputManager::onMouseMove(
			[this, pxUnit](Input& e)
			{
				if (!bingDragged)
					return;

				int posX = e.mouseX - e.mouseX % pxUnit;
				int posY = e.mouseY - e.mouseY % pxUnit;

				Math::Vector2 mouseToWorldPos{ camera->ScreenToWorldPoint(posX, posY + pxUnit) };
				gameObject->transform->position.Set(mouseToWorldPos);
			}
		);

		InputManager::onMouseButtonDown(MouseButton::Left,
			[this](Input& e)
			{
				if (bingDragged)
					return;
				auto mousevector = camera->ScreenToWorldPoint(e.mouseX, e.mouseY);
				if (Math::MathUtils::IsVector2WithinRect(mousevector, gameObject->transform->position, gameObject->transform->scale)){
					bingDragged = true;
				}
			}, "Ui:layer-" + LayerHelper::GetString(Layer::Default) // TODo dit dynamis maken
		);

		InputManager::onMouseButtonUp(MouseButton::Left,
			[this](Input& e)
			{
				if (bingDragged)
					bingDragged = false;

			}
		);
	}

	bool isBingDragged(){
		return bingDragged;
	}

private:
	bool bingDragged = true;
};