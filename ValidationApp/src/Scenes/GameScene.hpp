#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/PlayerBehaviour.hpp"

class GameScene : public Scene
{
public:
	GameScene(const std::string& name);

private:
	PlayerBehaviour* player = nullptr;
};