#pragma once

#include "Brush.hpp"

class EraserBrush : public Brush
{
public:
	static constexpr auto Name = "eraser";

	EraserBrush(GameObject* object, std::function<void(Brush*)> onRepeat)
		: Brush(Name, Key::KEY_Q, object, []() {}, []() {}, onRepeat)
	{

	}

protected:
	void OnActivate() override 
	{ 
		Repeat();
	}
};