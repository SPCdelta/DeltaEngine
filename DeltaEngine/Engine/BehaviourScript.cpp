#include "BehaviourScript.hpp"

void BehaviourScript::LoadScene(const std::string& name)
{
	transform->gameObject->LoadScene(name); 
}

void BehaviourScript::Destroy(std::shared_ptr<GameObject> gameObject)
{
	gameObject->Destroy();
}

void BehaviourScript::Destroy(GameObject* gameObject)
{
	gameObject->Destroy();
}

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

void BehaviourScript::onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category)
{
	_inputListeners.Add(InputManager::onMouseButtonDown(button, buttonEvent, category));
}

void BehaviourScript::onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category)
{
	_inputListeners.Add(InputManager::onMouseButtonUp(button, buttonEvent, category));
}

void BehaviourScript::onMouseMove(Events::EventCallback<Input&> mouseEvent) 
{
	_inputListeners.Add(InputManager::onMouseMove(mouseEvent));
}

void BehaviourScript::onMouseWheel(Events::EventCallback<Input&> wheelEvent) 
{
	_inputListeners.Add(InputManager::onMouseWheel(wheelEvent));
}

std::shared_ptr<GameObject> BehaviourScript::Instantiate()
{
	return transform->gameObject->Instantiate();
}

std::shared_ptr<GameObject> BehaviourScript::Instantiate(Transform transform)
{
	return transform.gameObject->Instantiate(transform);
}