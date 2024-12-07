#pragma once

#include "../Core/Math/MathUtils.hpp"
#include <functional>

namespace Ui
{
class Scrollable
{
public:

	Scrollable(Transform* transform, std::function<void(int)> func) {
	
		InputManager::onMouseWheel([func, transform](Input& e) {

			if (!Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, transform->position, transform->scale))
				return;

			int wheelDirection = 1;
			if (e.wheelVertically < 0)
				wheelDirection = -1;
			
			func(wheelDirection);
		});
	}

private:
	std::function<void(int)> _func; //Waarom is dit nodig om Registry te laten werken?
};
}