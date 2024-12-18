#include "Button.hpp"
#include "../Core/Math/MathUtils.hpp"

using namespace Ui;

void Button::SetOnLeftMouseClick(std::function<void()> func, const std::string& category)
{
	_inputListeners.Add(InputManager::onMouseButtonUp(
		MouseButton::Left,
		[this, func](Input& e)
		{
			if (func && Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _position, _scale))
			{
				func();
			}
		},
		category));
}

void Ui::Button::SetOnMouseHover(std::function<void()> func)
{
	_inputListeners.Add(InputManager::onMouseMove(
		[this, func](Input& e)
		{
			if (func && Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _position, _scale))
			{
				func();
			}
		}));
}

void Ui::Button::SetOnMousePressed(std::function<void()> func, const std::string& category)
{
	_inputListeners.Add(InputManager::onMouseButtonDown(
		MouseButton::Left,
		[this, func](Input& e)
		{
			if (func && Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _position, _scale))
			{
				func();
			}
		},
		category));
}

void Button::SetPosition(const Vector2& position)
{
	_position = position;
}

void Button::SetScale(const Vector2& scale)
{
	_scale = scale;
}
