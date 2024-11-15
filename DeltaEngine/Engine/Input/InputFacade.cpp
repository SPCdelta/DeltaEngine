#include "InputFacade.hpp"
#include <algorithm>

bool InputFacade::isInputEvent(SDL_Event event)
{
	return std::find(inputTypes.begin(), inputTypes.end(), event.type) !=
		   inputTypes.end();
}

void InputFacade::onKeyDown(SDL_Event event) {
	

}

void InputFacade::onKeyUp(SDL_Event event) {}

void InputFacade::onMouseMove(SDL_Event event) {}

void InputFacade::onMouseButtonPressed(SDL_Event event) {}

void InputFacade::onMouseButtonReleased(SDL_Event event) {}

void InputFacade::onMouseScroll(SDL_Event event) {}
