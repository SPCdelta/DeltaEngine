#include "Button.hpp"

#include "../Core/Math/MathUtils.hpp"

using namespace Ui;

Button::Button(Transform* transform) 
	: _transform{transform} 
{

}

void Button::SetOnLeftMouseClick(std::function<void()> func, const std::string& category)
{
	_inputListeners.Add(InputManager::onMouseButtonDown(
		MouseButton::Left,
		[this](Input& e)
		{
			_pressed = true;
		},
		category
	));

	_inputListeners.Add(InputManager::onMouseButtonUp(
		MouseButton::Left,
		[this, func](Input& e)
		{
			if (_pressed && func && Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY },_transform->position, _transform->scale))
			{
				if (e.consumed) return;
				e.consumed = true;
				func();
			}
			_pressed = false;
		},
		category
	));
}

void Ui::Button::SetOnMouseHover(std::function<void()> func)
{
	_inputListeners.Add(InputManager::onMouseMove(
		[this, func](Input& e)
		{
			if (func && Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _transform->position, _transform->scale))
			{
				func();
			}
		}
	));
}

void Ui::Button::SetOnMousePressed(std::function<void()> func, const std::string& category)
{
	_inputListeners.Add(InputManager::onMouseButtonDown(
		MouseButton::Left,
		[this, func](Input& e)
		{
			if (func && Math::MathUtils::IsPointWithinRect(Point{ e.mouseX, e.mouseY }, _transform->position, _transform->scale))
			{
				e.consumed = true;
				func();
			}
		},
		category
	));
}