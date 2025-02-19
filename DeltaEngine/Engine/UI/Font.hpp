#pragma once

#include <iostream>
#include <SDL_ttf.h>

#include "../Rendering/Rendering.hpp"
#include "../Core/Math/Vector2.hpp"

namespace Font
{
	using Font = TTF_Font;

	inline int InitializeTTF() 
	{
		return TTF_Init();
	}

	inline Font* OpenFont(const std::string& path, int size) 
	{
		return TTF_OpenFont(path.c_str(), size);
	}

	inline Rendering::Surface* RenderText_Solid(Font* font, const std::string& text, Rendering::Color color)
	{
		return TTF_RenderText_Solid(font, text.c_str(), color);
	}

	inline void CloseFont(Font* font)
	{
		TTF_CloseFont(font);
	}

	inline const char* GetError() 
	{
		return TTF_GetError(); 
	}

	inline void QuitTTF() 
	{
		TTF_Quit();
	}
}
