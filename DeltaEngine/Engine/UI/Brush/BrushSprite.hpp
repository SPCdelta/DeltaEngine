#pragma once

#include <iostream>
#include <vector>

#include "../../Input/InputManager.hpp"
#include "../../Transform.hpp"
#include "../../Rendering/Camera.hpp"
#include "SnapToGridBrush.hpp"

class BrushSprite
{
public:
	//Needs to get the SpriteName and Brush component
	BrushSprite(Transform& transform, const std::string& spriteName, SnapToGridBrush* brush)
	{
		std::string _category = "";
		_inputHandler.Add(InputManager::onMouseButtonDown(MouseButton::Left,
			[this, &transform, spriteName, brush](Input& e)
			{
				if (!Math::MathUtils::IsVector2WithinRect({ e.mouseX, e.mouseY }, transform.position, transform.scale))
					return;

				brush->SetSprite(spriteName);

			}, _category
		));
	};

private:
	//InputHandler _inputListeners;
	InputHandler _inputHandler{};
};