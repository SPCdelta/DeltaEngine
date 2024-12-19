#pragma once

#include "Brush.hpp"

#include "../../Core/Math/MathUtils.hpp"
#include "../../Rendering/Sprite.hpp"
#include "../../Core/Events/EventDispatcher.hpp"
#include "../../Input/InputHandler.hpp"

#include <algorithm>

class SnapToGridBrush : public Brush
{
public:
	static constexpr auto Name = "default";

	SnapToGridBrush(GameObject* object, std::function<void(Brush*)> onRepeat, Transform& screenViewport) 
		: Brush(Name, Key::KEY_E, object, []() {}, []() {}, onRepeat),
		_screenViewPort{ screenViewport }
	{
		_sprite->SetBorder(2);
		_sprite->SetBorderColor({ 100, 0, 0 });
	}

protected:
	void OnActivate() override
	{ 
		Repeat();
	}

private:
	void MouseToCanvase(Math::Point& mouse){
		if (static_cast<float>(mouse.GetX()) < _screenViewPort.position.GetX())
			mouse.SetX(static_cast<int>(_screenViewPort.position.GetX()));
		
		if (static_cast<float>(mouse.GetY()) < _screenViewPort.position.GetY())
			mouse.SetY(static_cast<int>(_screenViewPort.position.GetY()));
		
		if (static_cast<float>(mouse.GetX()) > _screenViewPort.scale.GetX())
			mouse.SetX(static_cast<int>(_screenViewPort.scale.GetX()));
		
		if (static_cast<float>(mouse.GetY()) > _screenViewPort.scale.GetY())
			mouse.SetY(static_cast<int>(_screenViewPort.scale.GetY()));

	}
	Transform& _screenViewPort;

	bool _pressed = false;
	bool _isActive = false;
};