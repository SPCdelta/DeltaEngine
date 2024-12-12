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
		_inputLocations.push_back(InputManager::onMouseButtonDown(MouseButton::Left,
			[this, &transform, spriteName, brush](Input& e)
			{
				if (!Math::MathUtils::IsVector2WithinRect({ e.mouseX, e.mouseY }, transform.position, transform.scale))
					return;

				std::cout << transform.position.GetX() << " klikt\n" ;
				brush->SetSprite(spriteName);

			}, _category
		));
	};


	~BrushSprite(){
		for (auto& input : _inputLocations)
		{
			InputManager::GetInstance().remove(input);
		}
		_inputLocations.clear();
	
	}

private:

	std::vector<InputLocation> _inputLocations;

};