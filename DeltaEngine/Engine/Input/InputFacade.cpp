#include "InputFacade.hpp"
#include <algorithm>
#include "KeyListener.hpp"

InputFacade::InputFacade() : inputManager(InputManager::GetInstance()){};

bool InputFacade::isInputEvent(SDL_Event event)
{
	return std::find(inputTypes.begin(), inputTypes.end(), event.type) !=
		   inputTypes.end();
}

void InputFacade::onInputEvent(SDL_Event event) {
	switch (event.type)
	{
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;

		case SDL_KEYUP:
			onKeyUp(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEWHEEL:
			onMouseScroll(event);
			break;
	}
}

void InputFacade::onKeyDown(SDL_Event event) {
	auto key = new KeyListener(SDL_GetKeyName(event.key.keysym.sym), true);
	inputManager.updateKeyDown(*key);
}

void InputFacade::onKeyUp(SDL_Event event) {
	auto key = new KeyListener(SDL_GetKeyName(event.key.keysym.sym), false);
	inputManager.updateKeyUp(*key);
}

void InputFacade::onMouseMove(SDL_Event event) {}

void InputFacade::onMouseButtonDown(SDL_Event event) {}

void InputFacade::onMouseButtonUp(SDL_Event event) {}

void InputFacade::onMouseScroll(SDL_Event event) {
	//std::cout << "Mouse wheel: X " << event.wheel.x << ", Y "
	//		  << event.wheel.y
	//		  << (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED
	//				  ? " (flipped)"
	//				  : "")
	//		  << std::endl;
}
