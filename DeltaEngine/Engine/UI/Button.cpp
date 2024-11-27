#include "Button.hpp"

using namespace Ui;

void Button::SetOnLeftMouseClick(void (*func)())
{
	InputManager::onMouseButtonDown(
		MouseButton::Left,
		[this, func](Input& e)
		{
			if (func && Vector2::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _position, _scale))
			{
				func();
			}
		},
		"Default_Button_Callback");
}