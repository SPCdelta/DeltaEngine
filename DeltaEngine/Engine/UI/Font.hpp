#pragma once
#include <iostream>
#include <SDL_ttf.h>
#include "../Rendering/Rendering.hpp"

namespace Font
{
	using Font = TTF_Font;

	inline int InitializeTTF() {
		return TTF_Init();
	}

	inline TTF_Font* OpenFont(const char* path, int size) {
		return TTF_OpenFont(path, size);
	}

	inline Rendering::Surface* RenderText_Solid(TTF_Font* font, const char* text, Rendering::Color color)
	{
		return TTF_RenderText_Solid(font, text, color);
	}

	inline void CloseFont(TTF_Font* font) {
		TTF_CloseFont(font);
	}

	inline const char* GetError() {
		return TTF_GetError(); 
	}

	inline void QuitTTF() {
		TTF_Quit();
	}
}

