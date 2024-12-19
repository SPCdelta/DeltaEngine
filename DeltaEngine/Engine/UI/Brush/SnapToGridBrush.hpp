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

	Transform& _screenViewPort;

	bool _pressed = false;
	bool _isActive = false;
};