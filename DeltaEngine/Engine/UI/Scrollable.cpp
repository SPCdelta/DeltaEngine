#include "Scrollable.hpp"

Ui::Scrollable::Scrollable(Transform* transform, std::function<void(int)> func)
{
	_scrollable = std::unique_ptr<InputListener>(InputManager::onMouseWheel([func, transform](Input& e) 
	{
		if (!Math::MathUtils::IsPointWithinRect(Math::Point{ e.mouseX, e.mouseY }, transform->position, transform->scale))
			return;

		int wheelDirection = 1;
		if (e.wheelVertically < 0)
			wheelDirection = -1;		
		func(wheelDirection);
	}));
}