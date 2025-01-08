#include "SpriteData.hpp"

SpriteData::SpriteData(Rendering::Texture* texture_, Math::Vector2 spriteStart_, Math::Vector2 spriteEnd_, const std::string& category_)
	: texture{texture_},
	  spriteStart{spriteStart_},
	  spriteEnd{spriteEnd_},
	  category{category_}
{

}