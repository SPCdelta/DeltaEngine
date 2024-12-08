#pragma once

#include "Engine/Delta.hpp"
#include "../IView.hpp"
#include <string>

class GameSpeedComponent : public IView
{
public:
	GameSpeedComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale);
private:
	const Uint8 DEFAULT_FONT_SIZE = 20; 
};

