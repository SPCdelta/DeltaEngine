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

KeyListener InputFacade::makeKeyStruct(SDL_Event event) {
	int posX = event.button.x;
	int posY = event.button.y;
	int pressed = event.key.state == SDL_PRESSED;
	return KeyListener({SDL_GetKeyName(event.key.keysym.sym)}, pressed, posX,
					   posY);
}

MouseListener InputFacade::makeMouseStruct(SDL_Event event)
{
	auto eButton = event.button;
	uint32_t which = eButton.which;
	int8_t button = eButton.button;
	int8_t clicks = eButton.clicks;
	int posY = eButton.y;
	int posX = eButton.x;
	return MouseListener(which, button, clicks, posY, posX);
}

void InputFacade::onKeyDown(SDL_Event event) {
	auto key = makeKeyStruct(event);
	inputManager.updateKeyDown(key);
}

void InputFacade::onKeyUp(SDL_Event event) {
	auto key = makeKeyStruct(event);
	inputManager.updateKeyUp(key);
}

void InputFacade::onMouseButtonDown(SDL_Event event) {
	auto click = makeMouseStruct(event);
	inputManager.updateMouseButtonDown(click);
}

void InputFacade::onMouseButtonUp(SDL_Event event) 
{
	auto click = makeMouseStruct(event);
	inputManager.updateMouseButtonUp(click);
}

void InputFacade::onMouseMove(SDL_Event event) {
	auto mouse = makeMouseStruct(event);
	inputManager.updateMouseMovement(mouse);
}

void InputFacade::onMouseScroll(SDL_Event event) {
	auto eWheel = event.wheel;
	int h = eWheel.x;
	int v = eWheel.y;
	uint32_t direction = eWheel.direction;
	
	float preciseX = eWheel.preciseX; 	
	float preciseY = eWheel.preciseY;	
	
	int mouseX = eWheel.mouseX;	
	int mouseY = eWheel.mouseY;

	auto wheel = WheelListener(h,v,direction,preciseX,preciseY,mouseX, mouseY);
	inputManager.updateMouseWheel(wheel);
}
