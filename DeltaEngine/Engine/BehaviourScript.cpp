#include "BehaviourScript.hpp"


void BehaviourScript::keyPressed(Key keyDown,
								 Events::EventCallback<Input&> keyEvent,
								 std::string category)
{
	registerdInputs.push_back(InputManager::keyPressed(keyDown, keyEvent, category));
}

void BehaviourScript::keyPressed(std::set<Key> keysDown,
								 Events::EventCallback<Input&> keyEvent, std::string category)
{
	registerdInputs.push_back(
		InputManager::keyPressed(keysDown, keyEvent, category));
}

void BehaviourScript::onKeyPressed(Key keyDown,
								   Events::EventCallback<Input&> keyEvent,
								   std::string category)
{
	registerdInputs.push_back(
		InputManager::onKeyPressed(keyDown, keyEvent, category));
}

void BehaviourScript::onKeyReleased(Key keyUp,
									Events::EventCallback<Input&> keyEvent,
									std::string category)
{
	registerdInputs.push_back(
		InputManager::onKeyReleased(keyUp, keyEvent, category));
}

void BehaviourScript::onMouseButtonDown(
	MouseButton button, Events::EventCallback<Input&> buttonEvent,
	std::string category)
{
	registerdInputs.push_back(
		InputManager::onMouseButtonDown(button, buttonEvent, category));
}

void BehaviourScript::onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category)
{
	registerdInputs.push_back(
		InputManager::onMouseButtonUp(button, buttonEvent, category));
}

void BehaviourScript::onMouseMove(Events::EventCallback<Input&> mouseEvent) {
	registerdInputs.push_back(InputManager::onMouseMove(mouseEvent));
}

void BehaviourScript::onMouseWheel(Events::EventCallback<Input&> wheelEvent) {
	registerdInputs.push_back(InputManager::onMouseWheel(wheelEvent));
}