#include "PlayerInput.hpp"

PlayerInput::PlayerInput(BehaviourScript* behaviour)
{
	// Input
	behaviour->onKeyPressed(KEY_W, [this](Input& e) { _wDown = true; }, "Gameplay");
	behaviour->onKeyPressed(KEY_S, [this](Input& e) { _sDown = true; }, "Gameplay");
	behaviour->onKeyPressed(KEY_A, [this](Input& e) { _aDown = true; }, "Gameplay");
	behaviour->onKeyPressed(KEY_D, [this](Input& e) { _dDown = true; }, "Gameplay");

	behaviour->onKeyReleased(KEY_W, [this](Input& e) { _wDown = false; }, "Gameplay");
	behaviour->onKeyReleased(KEY_S, [this](Input& e) { _sDown = false; }, "Gameplay");
	behaviour->onKeyReleased(KEY_A, [this](Input& e) { _aDown = false; }, "Gameplay");
	behaviour->onKeyReleased(KEY_D, [this](Input& e) { _dDown = false; }, "Gameplay");	
}

const Math::Vector2 PlayerInput::GetDirection() const 
{ 
	return { static_cast<float>(-_aDown + _dDown), static_cast<float>(_wDown + -_sDown) };
}