#pragma once

#include <string>

#include "../Core/Math/Vector2.hpp"
#include "Rendering.hpp"

class SpriteData
{
public:
	SpriteData(Rendering::Texture* texture_, Math::Vector2 spriteStart_, Math::Vector2 spriteEnd_)
		: texture{texture_}, spriteStart{spriteStart_}, spriteEnd{spriteEnd_}
	{

	}

	Rendering::Texture* texture;
	Math::Vector2 spriteStart;
	Math::Vector2 spriteEnd;
};