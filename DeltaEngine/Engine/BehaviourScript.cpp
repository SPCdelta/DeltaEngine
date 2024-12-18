#include "BehaviourScript.hpp"


void BehaviourScript::keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category)
{
	_inputListeners.Add(InputManager::keyPressed(keyDown, keyEvent, category));
}

void BehaviourScript::keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, std::string category)
{
	_inputListeners.Add(InputManager::keyPressed(keysDown, keyEvent, category));
}

void BehaviourScript::onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category)
{
	_inputListeners.Add(InputManager::onKeyPressed(keyDown, keyEvent, category));
}

void BehaviourScript::onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, std::string category)
{
	_inputListeners.Add(InputManager::onKeyReleased(keyUp, keyEvent, category));
}

void BehaviourScript::onMouseButtonDown(
	MouseButton button, Events::EventCallback<Input&> buttonEvent,
	std::string category)
{
	_inputListeners.Add(InputManager::onMouseButtonDown(button, buttonEvent, category));
}

void BehaviourScript::onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category)
{
	_inputListeners.Add(InputManager::onMouseButtonUp(button, buttonEvent, category));
}

void BehaviourScript::onMouseMove(Events::EventCallback<Input&> mouseEvent) {
	_inputListeners.Add(InputManager::onMouseMove(mouseEvent));
}

void BehaviourScript::onMouseWheel(Events::EventCallback<Input&> wheelEvent) {
	_inputListeners.Add(InputManager::onMouseWheel(wheelEvent));
}