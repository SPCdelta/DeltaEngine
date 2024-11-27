#pragma once

#include "Engine/Delta.hpp"

class PlayerInput
{
public:
	PlayerInput()
	{
		// Input
		InputManager::activateCategory("Gameplay");
		InputManager::onKeyPressed(KEY_W, [this](Input& e) { _wDown = true; }, "Gameplay");
		InputManager::onKeyPressed(KEY_S, [this](Input& e) { _sDown = true; }, "Gameplay");
		InputManager::onKeyPressed(KEY_A, [this](Input& e) { _aDown = true; }, "Gameplay");
		InputManager::onKeyPressed(KEY_D, [this](Input& e) { _dDown = true; }, "Gameplay");

		InputManager::onKeyReleased(KEY_W, [this](Input& e) { _wDown = false; }, "Gameplay");
		InputManager::onKeyReleased(KEY_S, [this](Input& e) { _sDown = false; }, "Gameplay");
		InputManager::onKeyReleased(KEY_A, [this](Input& e) { _aDown = false; }, "Gameplay");
		InputManager::onKeyReleased(KEY_D, [this](Input& e) { _dDown = false; }, "Gameplay");
	}

	const Math::Vector2 GetDirection() const 
	{ 
		return { static_cast<float>(-_aDown + _dDown), static_cast<float>(_wDown + -_sDown) };
	}

private:
	int _wDown{false};
	int _sDown{false};
	int _aDown{false};
	int _dDown{false};
};