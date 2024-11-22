#include "BehaviourScript.hpp"

void BehaviourScript::SetGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

BehaviourScript::~BehaviourScript() {
	unregesterInputs();
}

void BehaviourScript::keyPressed(Key keyDown,
								 Events::EventCallback<Input&> keyEvent,
								 std::string category)
{
	regesterdInputs.push_back(InputManager::keyPressed(keyDown, keyEvent, category));
}

void BehaviourScript::keyPressed(std::set<Key> keysDown,
								 Events::EventCallback<Input&> keyEvent, std::string category)
{
	regesterdInputs.push_back(
		InputManager::keyPressed(keysDown, keyEvent, category));
}

void BehaviourScript::onKeyPressed(Key keyDown,
								   Events::EventCallback<Input&> keyEvent,
								   std::string category)
{
	regesterdInputs.push_back(
		InputManager::onKeyPressed(keyDown, keyEvent, category));
}

void BehaviourScript::onKeyRealesed(Key keyUp,
									Events::EventCallback<Input&> keyEvent,
									std::string category)
{
	regesterdInputs.push_back(
		InputManager::onKeyRealesed(keyUp, keyEvent, category));
}

void BehaviourScript::onMouseButtonDown(
	Button button, Events::EventCallback<Input&> buttonEvent,
	std::string category)
{
	regesterdInputs.push_back(
		InputManager::onMouseButtonDown(button, buttonEvent, category));
}

void BehaviourScript::onMouseButtonUp(Button button,
									  Events::EventCallback<Input&> buttonEvent,
									  std::string category)
{
	regesterdInputs.push_back(
		InputManager::onMouseButtonUp(button, buttonEvent, category));
}

void BehaviourScript::onMouseMove(Events::EventCallback<Input&> mouseEvent) {
	regesterdInputs.push_back(InputManager::onMouseMove(mouseEvent));
}

void BehaviourScript::onMouseWheel(Events::EventCallback<Input&> wheelEvent) {
	regesterdInputs.push_back(InputManager::onMouseWheel(wheelEvent));
}

void BehaviourScript::unregesterInputs() {
	for (auto& input : regesterdInputs)
	{
		InputManager::GetInstance().remove(input);
	}
}
