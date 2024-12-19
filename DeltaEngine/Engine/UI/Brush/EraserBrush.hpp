#pragma once

#include "Brush.hpp"

class EraserBrush : public Brush
{
public:
	static constexpr auto Name = "eraser";

	EraserBrush()
		: Brush(Name)
	{

	}
};