#pragma once

#include "Engine/Delta.hpp"

#include "../Views/MenuView.hpp"

class DevScene : public Scene
{
public:
	DevScene(const std::string& name);

	void OnStart() override;
};