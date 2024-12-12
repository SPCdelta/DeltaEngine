#pragma once

#include "../../Core/Math/Vector2.hpp"

struct Particle
{
	Transform* transform;
	Vector2 direction; // Travel Direction
	float speed; // Units per second
	float rotationSpeed; // Rotations per second
	float aliveFor; // Alive for seconds
};