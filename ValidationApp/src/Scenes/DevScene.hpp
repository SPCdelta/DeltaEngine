#pragma once

#include "Engine/Delta.hpp"
#include "../Views/MenuView.hpp"

class DevScene : public Scene
{
public:
	DevScene(const std::string& name) : Scene{name}
	{
		MenuView menuView{ *this, "Dev Menu", 4, "Assets\\Fonts\\knight_warrior.otf", {500, 100}, {300, 100}, 50, 80 };
	}
};