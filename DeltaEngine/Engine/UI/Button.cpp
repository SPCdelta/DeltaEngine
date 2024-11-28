#include "Button.hpp"

using namespace Ui;

void Button::SetOnLeftMouseClick(std::function<void()> func, const std::string& category)
{
	// Hier moet nog gecontrolleerd worden of de functie al is gezet, anders overschrijf de vorige functie.
	InputManager::onMouseButtonDown(
		MouseButton::Left,
		[this, func](Input& e)
		{
			if (func && Vector2::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _position, _scale))
			{
				func();
			}
		},
		category);
}

void Button::SetPosition(const Vector2& position)
{
	_position = position;
}

void Button::SetScale(const Vector2& scale)
{
	_scale = scale;
}
