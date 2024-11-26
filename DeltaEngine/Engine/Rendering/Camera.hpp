#pragma once

#include "../Transform.hpp"

class Camera
{
public:
	Camera(Transform& cameraTransform) 
		: transform{cameraTransform}
	{

	}

	void SetPosition(const Math::Vector2 position)
	{ 
		transform.position.Set(position);
	}

	Transform& transform;
};