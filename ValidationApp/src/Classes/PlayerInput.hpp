#pragma once

#include "Engine/Delta.hpp"

class PlayerInput
{
public:
	PlayerInput(BehaviourScript* behaviour);

	const Math::Vector2 GetDirection() const;

private:
	int _wDown{false};
	int _sDown{false};
	int _aDown{false};
	int _dDown{false};
};