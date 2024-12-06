#pragma once

#include "Transform.hpp"

struct TransformDTO
{
	float posX, posY;
	float rotation;
	float scaleX, scaleY;

	Transform ToTransform() const
	{
		return Transform{{posX, posY}, rotation, {scaleX, scaleY}};
	}
};
