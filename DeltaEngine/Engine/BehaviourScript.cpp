
void BehaviourScript::SetGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

BehaviourScript::~BehaviourScript() {
	unregisterInputs();
}

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
	Button button, Events::EventCallback<Input&> buttonEvent,
	std::string category)
{
	registerdInputs.push_back(
		InputManager::onMouseButtonDown(button, buttonEvent, category));
}

void BehaviourScript::onMouseButtonUp(Button button,
									  Events::EventCallback<Input&> buttonEvent,
									  std::string category)
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

void BehaviourScript::unregisterInputs() {
	for (auto& input : registerdInputs)
	{
		InputManager::GetInstance().remove(input);
	}
}
