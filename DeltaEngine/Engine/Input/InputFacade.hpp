#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>

class InputFacade
{
public:

	bool isInputEvent(SDL_Event event);

	void onKeyDown(SDL_Event event);
	void onKeyUp(SDL_Event event);
	void onMouseMove(SDL_Event event);
	void onMouseButtonPressed(SDL_Event event);
	void onMouseButtonReleased(SDL_Event event);
	void onMouseScroll(SDL_Event event);

private:
	const std::vector<SDL_EventType> inputTypes{
		SDL_KEYDOWN, SDL_KEYUP, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP, SDL_MOUSEMOTION, SDL_MOUSEWHEEL};
};
