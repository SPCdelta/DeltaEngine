#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"
#include "../Scripts/MouseFollowBehaviour.hpp"
#include "../Scripts/DummyBehaviour.hpp"

class GameScene : public Scene
{
public:
	GameScene(const std::string& name);

private:
	//PlayerBehaviour* player = nullptr;
};