#pragma once

#include <memory>

#include "Core/Math/Vector2.hpp"

class GameObject;

struct Transform
{
	Math::Vector2 position{ 0.0f, 0.0f };
	float rotation{ 0.0f };
	Math::Vector2 scale{ 0.0f, 0.0f };
	std::shared_ptr<GameObject> gameObject;

	Transform operator+(const Transform& other) const 
	{
		Transform result = *this;
		result.position = this->position + other.position;
		result.rotation = this->rotation + other.rotation;
		result.scale = this->scale + other.scale;
		return result;
	}
};