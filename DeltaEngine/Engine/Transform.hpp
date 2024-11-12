#pragma once

#include "Core/Math/Vector2.hpp"

struct Transform
{
	Math::Vector2 position{ 0.0f, 0.0f };
	float rotation{ 0.0f };
	Math::Vector2 scale{ 0.0f, 0.0f };
};