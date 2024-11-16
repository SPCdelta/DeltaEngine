#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>
#include "InputManager.hpp"

class InputFacade
{
public:
	InputFacade();

	bool isInputEvent(SDL_Event event);

	void onInputEvent(SDL_Event event);

	KeyListener makeKeyStruct(SDL_Event event);
	MouseListener makeMouseStruct(SDL_Event event);

	void onKeyDown(SDL_Event event);
	void onKeyUp(SDL_Event event);
	void onMouseMove(SDL_Event event);
	void onMouseButtonDown(SDL_Event event);
	void onMouseButtonUp(SDL_Event event);
	void onMouseScroll(SDL_Event event);

private:
	const std::vector<SDL_EventType> inputTypes{
		SDL_KEYDOWN, SDL_KEYUP, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP, SDL_MOUSEMOTION, SDL_MOUSEWHEEL};

	InputManager& inputManager;
};
