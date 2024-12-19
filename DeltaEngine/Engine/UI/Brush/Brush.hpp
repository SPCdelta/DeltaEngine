#pragma once

#include <string>
#include <functional>

class Brush
{
public:
	Brush(const std::string& name, std::function<void()> onActivate, std::function<void()> onRelease)
		: _name{ name }, _categoryName{ "brush_" + name }, _onActivate{ onActivate }, _onRelease{ onRelease }
	{
		inputHandler.Add(InputManager::onMouseButtonDown(MouseButton::Left, 
			[this](Input& e)
			{
				_onActivate();
			}, ("brush_" + _name)
		));

		inputHandler.Add(InputManager::onMouseButtonUp(MouseButton::Left,
			[this](Input& e)
			{
				_onRelease();
			}, ("brush_" + _name)
		));
	}

	void Enable() const
	{
		InputManager::activateCategory(_categoryName);
	}

	void Disable() const
	{
		InputManager::deactivateCategory(_categoryName);
	}

	const std::string& GetName() const { return _name; }

private:
	std::string _name;
	std::string _categoryName;
	std::function<void()> _onActivate;
	std::function<void()> _onRelease;
	InputHandler inputHandler;
};