#pragma once

#include "../Core/Math/MathUtils.hpp"
#include "../Input/InputManager.hpp"

namespace Ui
{
class Scrollable
{
public:

	Scrollable(Transform* transform, std::function<void(int)> func) {
	
		_scrollebole = InputManager::onMouseWheel([func, transform](Input& e) {

			if (!Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, transform->position, transform->scale))
				return;

			int wheelDirection = 1;
			if (e.wheelVertically < 0)
				wheelDirection = -1;
			
			func(wheelDirection);
		});
	}

	~Scrollable(){
		InputManager::GetInstance().remove(_scrollebole);
	}

private:
	InputLocation _scrollebole;

};
}