#include "Button.hpp"
#include "../Core/Math/MathUtils.hpp"

using namespace Ui;

void Button::SetOnLeftMouseClick(std::function<void()> func, const std::string& category)
{
	// Hier moet nog gecontrolleerd worden of de functie al is gezet, anders overschrijf de vorige functie.
	InputManager::onMouseButtonDown(
		MouseButton::Left,
		[this, func](Input& e)
		{
			if (func && Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _position, _scale))
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
