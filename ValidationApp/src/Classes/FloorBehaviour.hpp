#pragma once

#include "Engine/Delta.hpp"

enum class FloorType
{
	NORMAL = 0,
	ICE = 1,
	MUD = 2,
};

class FloorBehaviour
{
public:
	FloorBehaviour(Rigidbody& rigidbody);
	~FloorBehaviour();

	FloorType GetOnFloor() const;

private:
	Rigidbody& _rigidbody;

	int _iceCount{0};
	int _mudCount{0};
};