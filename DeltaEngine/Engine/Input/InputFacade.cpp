#include "InputFacade.hpp"
#include <algorithm>

InputFacade::InputFacade() : inputManager(InputManager::GetInstance()){
};

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
	auto it = SDLToDeltaKeys.find(event.key.keysym.sym);

	Key input = KEY_UNKNOWN;
	if (it != SDLToDeltaKeys.end())
		input = it->second;

	inputManager.updateKeyDown(input);
}

void InputFacade::onKeyUp(SDL_Event event) {
	auto it = SDLToDeltaKeys.find(event.key.keysym.sym);

	Key input = KEY_UNKNOWN;
	if (it != SDLToDeltaKeys.end())
		input = it->second;
	inputManager.updateKeyUp(input);
}

void InputFacade::onMouseButtonDown(SDL_Event event) {
	inputManager.updateMouseButtonDown(InputsEnum::toButton(event.button.button));
}

void InputFacade::onMouseButtonUp(SDL_Event event) 
{
	inputManager.updateMouseButtonUp(InputsEnum::toButton(event.button.button));
}

void InputFacade::onMouseMove(SDL_Event event) {
	inputManager.updateMouseMovement({event.button.x, event.button.y});
}

void InputFacade::onMouseScroll(SDL_Event event) {
	auto eWheel = event.wheel;
	int v = eWheel.y;

	inputManager.updateMouseWheel(v);
}
